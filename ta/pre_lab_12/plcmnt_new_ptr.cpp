#include <iostream>

struct BigDmInteger {
  BigDmInteger(int v) : _value{new int(v)} {}
  ~BigDmInteger() { delete _value; }
  int value() const { return *_value; }

  BigDmInteger(const BigDmInteger &) = delete;
  BigDmInteger& operator=(const BigDmInteger &) = delete;
  BigDmInteger(const BigDmInteger &&) = delete;
  BigDmInteger& operator=(BigDmInteger &&) = delete;
private:
  int *_value;
};

std::ostream& operator<<(std::ostream &s, const BigDmInteger &bi) {
  return s << bi.value();
}

void enjoy_free_memory(void *bi_mem) {
  // "free" means "you don't have to manage it"

  BigDmInteger *bdmi = new (bi_mem) BigDmInteger{42};
  std::cout << *bdmi << std::endl;
  // NB: mem leak w/o explicit dtor call;
  //     "delete bdmi;" is not an option.
  bdmi->~BigDmInteger();
}

// arbitrary consts
constexpr int ChunkSize = 400;
constexpr int PayloadOffset = 222;
static_assert(sizeof(BigDmInteger) <= ChunkSize - PayloadOffset,
	      "Payload sz is not sufficient to store BigDmInteger");

int main(int, char**) {
  // the main function maintains "memory" life time
  char *memory = new char[ChunkSize];
  enjoy_free_memory(memory + PayloadOffset);
  delete [] memory;

  return 0;
}
