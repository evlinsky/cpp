#include <iostream>
#include <string>

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

template <BitOrder ClientOrder = BitOrder::LittleEndian>
class BitEndiannessAwareBlob : public NonCpMvable {
private:
  template <int N> class BlobInt;
public:
  BitEndiannessAwareBlob(const std::string &bits, BitOrder src_endianness)
    : _sz{bits.size()}, _blob{new uint8_t[_sz]}, _endianness{src_endianness} {
    uint8_t *bit_ptr = _blob;
    for (uint8_t bit : bits) {
      *bit_ptr++ = bit - '0';
    }
  }

  ~BitEndiannessAwareBlob() {
    delete [] _blob;
  }

  BlobInt<8> int8(std::size_t offset_bits) {
    return BlobInt<8>{_blob + offset_bits, _endianness};
  }

  BlobInt<16> int16(std::size_t offset_bits) {
    return BlobInt<16>{_blob + offset_bits, _endianness};
  }

private:
  template <int N>
  class BlobInt {
  private:
    static_assert(N % 8 == 0, "N is not byte-aligned");
  public:
    BlobInt(uint8_t *data, BitOrder be) : _data{data}, _blob_endss{be} {}

    BlobInt<N>& operator=(int value) {
      uint8_t *bit_ptr = _data;
      for (int i = 0; i < N; ++i) {
        int bit_pos = fix_bit_pos(i);
        *bit_ptr++ = (value & ((int)1) << bit_pos) >> bit_pos;
      }

      return *this;
    }

    operator int() const {
      int user_endss_int = 0;
      uint8_t *bit_ptr = _data;
      for (int i = 0; i < N; ++i) {
        user_endss_int |= ((int)*bit_ptr++) << fix_bit_pos(i);
      }
      return user_endss_int;
    }
  private:
    int fix_bit_pos(int bit_pos) const {
      return _blob_endss == ClientOrder ? bit_pos : N - 1 - bit_pos;
    }
  private:
    uint8_t *_data;
    BitOrder _blob_endss;
  };

  template <BitOrder CO>
  friend std::ostream& operator<<(std::ostream &os,
                                  const BitEndiannessAwareBlob<CO> &blob);
private:
  std::size_t _sz;
  uint8_t *_blob; // I wish I had an implementation of my_array<bool>...
  BitOrder _endianness;
};

template <BitOrder CO>
std::ostream& operator<<(std::ostream &os, const BitEndiannessAwareBlob<CO> &blob) {
  os << (blob._endianness == BitOrder::BigEndian ? "BE" : "LE");
  std::size_t i = 0;
  while (true) {
    if      (i % 8 == 0) { os << '|'; }
    else if (i % 4 == 0) { os << '.'; }
    
    if (blob._sz <= i) { break; }
    os << (char)(blob._blob[i] + '0');
    i++;
  }
  return os;
}

const std::string Blob_Value = "100000100000000101101001";
int main(int, char**) {
  BitEndiannessAwareBlob<> blob(Blob_Value, BitOrder::BigEndian);
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
