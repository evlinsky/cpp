#include <iostream>

struct Character {
  Character() { std::cout << __func__ << std::endl; }
  virtual ~Character() { std::cout << __func__ << std::endl; }
};

struct MovieCharacter : Character {
  MovieCharacter() { std::cout << __func__ << std::endl; }
  ~MovieCharacter() override { std::cout << __func__ << std::endl; }
};

struct Warrior {
  Warrior(int i) { std::cout << __func__ << " " << i << std::endl; }
  virtual ~Warrior() { std::cout << __func__ << std::endl; }
};

struct Animal {
  Animal(int i) { std::cout << __func__ << " " << i << std::endl; }
  virtual ~Animal() { std::cout << __func__ << std::endl; }
};

struct Bear : virtual Animal {
  Bear() : Animal(1) { std::cout << __func__ << std::endl; }
  ~Bear() override { std::cout << __func__ << std::endl; }
};

struct Racoon : virtual Animal {
  Racoon() : Animal(2) { std::cout << __func__ << std::endl; }
  ~Racoon() override { std::cout << __func__ << std::endl; }
};

struct Panda : Bear, Racoon {
  Panda() : Animal(3) { std::cout << __func__ << std::endl; }
  ~Panda() override { std::cout << __func__ << std::endl; }
};

struct KungFuPanda : Panda, MovieCharacter, virtual Warrior {
  KungFuPanda() : Animal(4), Warrior(1) { std::cout << __func__ << std::endl; }
  ~KungFuPanda() override { std::cout << __func__ << std::endl; }
};

int main(int, char**) {
  {
    std::cout << "== Panda\n";
    Panda p;
  }
  std::cout << std::endl;
  {
    std::cout << "==KFPanda\n";
    KungFuPanda kfp;
  }
}
