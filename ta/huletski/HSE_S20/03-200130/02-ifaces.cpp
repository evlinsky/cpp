#include <iostream>
#include <string>
#include <vector>

//// "Framework"

struct PhysicalObject {
  virtual void update_pos() = 0;
  virtual ~PhysicalObject() {}
};

// NB: ...able
struct Displayable {
  virtual void show() const = 0;
  virtual ~Displayable() {}
};

using Displayables = std::vector<Displayable*>;

void show_all(const Displayables& objs) {
  for (Displayable *d : objs) {
    d->show();
    std::cout << " ";
  }
  std::cout << "\n";
}

using physicalwoldobjects = std::vector<physicalobject*>;

void update_world(const physicalwoldobjects& objs) {
  for (physicalobject *po : objs) {
    po->update_pos();
    // po->show() // unknown method
  }
}

//// framework extension

struct person : physicalobject, displayable {
  person(const std::string &name, int x, int y)
    : x_{x}, y_{y}, name_{name} {}
  void update_pos() override {
    x_++;
    y_++;
  }
  void show() const override {
    std::cout << name_ << "(" << x_ << ", " << y_ << ")";
  }
private:
  int x_, y_;
  std::string name_;
};

int main(int, char **) {
  displayables d;
  PhysicalWoldObjects pwo;

  Person joe("Joe", 2, 1), bob("Bob", 0, 0);
  d.push_back(&joe);
  d.push_back(&bob);
  pwo.push_back(&joe);
  pwo.push_back(&bob);

  update_world(pwo);
  show_all(d);
}
