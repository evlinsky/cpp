#include <iostream>
#include <string>

class Foo {
public:
  Foo(const std::string &id) : id_{id} {}
  Foo& operator=(const Foo&) {
    std::cout << "Foo(" << id_ << "):op=" << std::endl;
    return *this;
  }
  Foo(const Foo&) = default;
  ~Foo() = default;
  Foo&& operator=(Foo&&) = delete;
private:
  std::string id_;
};

class Base {
public:
  Base() : f_("Base_f") {
    std::cout << "Base ctor" << std::endl;
  }
private:
  Foo f_;
};

class Left : public Base {};
class Right : public Base {};
class Join : public Left, public Right {
public:
  Join() : Base(), Right(), Left() {}
};

int main(int, char**) {
  Join j1, j2;
  j1 = j2;
}
