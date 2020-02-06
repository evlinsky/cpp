#include <stdexcept>
#include <iostream>

struct Object {
  Object(const std::string &s) : id_(s) {}
  ~Object() { std::cout << "~Obj(" << id_ << ")\n"; }
private:
  std::string id_;
};

void foo() {
  Object foo1("foo1");
  throw std::runtime_error("foo exception");
  Object foo2("foo2");
}

void bar() {
  Object bar0("bar0");
  int *i = new int[5];
  {
    Object bar1("bar1");
    foo();
    Object bar2("bar2");
    i[0] = 5;
  }
  delete [] i;
}

int main(int, char**) {
  Object main0("main0");
  try {
    Object main1("main1");
    bar();
    Object main2("main2");
  } catch (const std::exception &e) {
    std::cout << e.what() << std::endl;
  }
}
