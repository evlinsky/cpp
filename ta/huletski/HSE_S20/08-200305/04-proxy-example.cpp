#include <iostream>
#include <string>
#include <cstdint>
#include <cassert>
#include <iomanip>

// NB: _bit_ not byte.
enum class BitOrder { BigEndian, LittleEndian };

class NonCpMvable { // non-copyable, non-moveable
public:
  NonCpMvable() {}
  NonCpMvable(const NonCpMvable&) = delete;
  NonCpMvable(NonCpMvable&&) = delete;
  NonCpMvable& operator=(const NonCpMvable&) = delete;
  NonCpMvable& operator=(NonCpMvable&&) = delete;
};

template <BitOrder RequiredBitOrder = BitOrder::LittleEndian>
class BitEndiannessAwareBlob : public NonCpMvable {
private:
  template <std::size_t N> class BlobInt;
public:
  BitEndiannessAwareBlob(const std::string &bits, BitOrder src_bit_order)
    : _sz{bits.size()}, _blob{new uint8_t[_sz]}
    , _src_bit_order{src_bit_order} {
    uint8_t *bit_ptr = _blob;
    for (uint8_t bit : bits) {
      *bit_ptr++ = bit - '0';
    }
  }

  ~BitEndiannessAwareBlob() {
    delete [] _blob;
  }

  BlobInt<8> int8(std::size_t offset_bits) {
    return BlobInt<8>{_blob + offset_bits, _src_bit_order};
  }

  BlobInt<16> int16(std::size_t offset_bits) {
    return BlobInt<16>{_blob + offset_bits, _src_bit_order};
  }

  template <BitOrder CO>
  friend std::ostream& operator<<(std::ostream &os,
                                  const BitEndiannessAwareBlob<CO> &blob) {
    os << (blob._src_bit_order == BitOrder::BigEndian ? "BE" : "LE");
    std::size_t i = 0;
    while (true) {
      if      (i % 8 == 0) { os << '|'; }
      else if (i % 4 == 0) { os << '.'; }

      if (blob._sz <= i) { break; }
      os << static_cast<char>(blob._blob[i] + '0');
      i++;
    }
    return os;
  }

private:
  template <std::size_t BitsNm>
  class BlobInt {
  private:
    static_assert(BitsNm % 8 == 0, "BitsNm is not byte-aligned");
  public:
    BlobInt(uint8_t *data, BitOrder be) : _data{data}, _blob_endss{be} {}

    BlobInt<BitsNm>& operator=(int client_int) {
      uint8_t *bit_ptr = _data;
      for (std::size_t i = 0; i < BitsNm; ++i) {
        std::size_t bit_pos = convert_bit_i(i); // client bit i -> blob bit i
        *bit_ptr++ = (client_int & (1UL << bit_pos)) >> bit_pos;
      }
      return *this;
    }

    operator int() const {
      int client_int = 0; // client bit order
      uint8_t *bit_ptr = _data;
      for (std::size_t i = 0; i < BitsNm; ++i) {
        client_int |= static_cast<uint64_t>(*bit_ptr++) << convert_bit_i(i);
      }
      return client_int;
    }
  private:
    std::size_t convert_bit_i(std::size_t src_bit_i) const {
      assert(src_bit_i + 1 <= BitsNm);
      return _blob_endss == RequiredBitOrder ? src_bit_i
                                             : BitsNm - 1 - src_bit_i;
    }
  private:
    uint8_t *_data;
    BitOrder _blob_endss;
  };

private:
  std::size_t _sz;
  uint8_t *_blob; // I wish I had an implementation of my_array<bool>...
  BitOrder _src_bit_order;
};

int main(int, char**) {
  const std::string Blob_Value = "100000100000000101101001";

  BitEndiannessAwareBlob<> blob(Blob_Value, BitOrder::BigEndian);
  std::cout << std::hex;
  std::cout << "Init blob" << std::endl;
  std::cout << blob << std::endl;
  std::cout << "== Test blob output ==" << std::endl;
  std::cout << "int8, offset 8: ";
  std::cout << blob.int8(8) << std::endl;
  std::cout << "int16, offset 6: ";
  std::cout << blob.int16(6) << std::endl;

  std::cout << "== Test blob input ==" << std::endl;
  {
    BitEndiannessAwareBlob<> blob(Blob_Value, BitOrder::BigEndian);
    std::cout << "int8, offset 4: ";
    blob.int8(4) = 0x0F;
    std::cout << blob << std::endl;
    std::cout << "Stored: " << blob.int8(4) << std::endl;
  }
  {
    BitEndiannessAwareBlob<> blob(Blob_Value, BitOrder::LittleEndian);
    std::cout << "int16, offset 7: ";
    blob.int16(7) = 0x00AF;
    std::cout << blob << std::endl;
    std::cout << "Stored: " << blob.int16(7) << std::endl;
  }
}
