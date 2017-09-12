#include <list>
#include <algorithm>
#include <iostream>

class Arena;

// placement <...>
void* operator new(std::size_t, Arena &);

class Arena {
public:
  void* alloc(std::size_t sz) {
    void *ptr = new char[sz]();
    _ptrs.push_back(ptr);
    return ptr;
  }

  void free(void *ptr) {
    auto ptr_it = std::find(_ptrs.begin(), _ptrs.end(), ptr);
    if (ptr_it == _ptrs.end()) { return; }
    _ptrs.erase(ptr_it); // stop ptr tracking
    free_ptr(ptr);
  }

  Arena() = default;
  ~Arena() {
    for (void *ptr : _ptrs) {
      free_ptr(ptr);
    }
  }
private: //methods

  void free_ptr(void *ptr) {
    char *ch_ptr = reinterpret_cast<char *>(ptr); // i.e. (char*) ptr
    delete [] ch_ptr;
  }

private: // members
  std::list<void *> _ptrs;
private: // ctors/op=
  Arena(const Arena &) = delete;
  Arena(Arena &&) = delete;
  Arena& operator=(const Arena &) = delete;
  Arena& operator=(Arena &&) = delete;
};

void* operator new(std::size_t sz, Arena &a) {
  return a.alloc(sz);
}

void operator delete(void *ptr, Arena &a) {
  a.free(ptr);
}

//------------------------------ Arena in action -----------------------------//

struct BigInteger {
  BigInteger(int v) : value{v} {}
  int value;
};

BigInteger operator+(const BigInteger &lhs, const BigInteger &rhs) {
  return BigInteger{lhs.value + rhs.value};
}

std::ostream& operator<<(std::ostream &s, const BigInteger &bi) {
  return s << bi.value;
}

void bi_sum_example() {
  Arena bi_arena;
  auto i = new (bi_arena) BigInteger(2);
  auto j = new (bi_arena) BigInteger(2);
  std::cout << *i + *j << std::endl;
  // NB: bi_arena cleans up both i and j
}

//-------------------------------- Mem leak ----------------------------------//

struct BigDmInteger {
  BigDmInteger(int v) : _value{new int(v)} {}
  ~BigDmInteger() { delete _value; }
  int value() const { return *_value; }

  BigDmInteger(BigDmInteger &&that) = delete;
  BigDmInteger(const BigDmInteger &) = delete;
  BigDmInteger& operator=(const BigDmInteger &) = delete;
  BigDmInteger& operator=(BigDmInteger &&) = delete;
private:
  int *_value;
};

std::ostream& operator<<(std::ostream &s, const BigDmInteger &bi) {
  return s << bi.value();
}

void bi_delete_example() {
  Arena bi_dm_arena;
  auto i = new (bi_dm_arena) BigDmInteger(2);
  std::cout << *i << std::endl;
  // TODO: fix mem leak by uncommenting a correct option:
  // // There is no mem leak, idiot!
  // delete (bi_dm_arena) i;
  // delete i;
  // ::operator delete (i, bi_dm_arena);
  // i->~BigDmInteger(); /* ::operator delete (i, bi_dm_arena); */
}

//----------------------------------------------------------------------------//

int main(int, char**) {
  bi_sum_example();
  bi_delete_example();

  return 0;
}

