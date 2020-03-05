#include <iostream>

class NonCpMvable { // non-copyable, non-moveable
public:
  NonCpMvable() {}
  NonCpMvable(const NonCpMvable&) = delete;
  NonCpMvable(NonCpMvable&&) = delete;
  NonCpMvable& operator=(const NonCpMvable&) = delete;
  NonCpMvable& operator=(NonCpMvable&&) = delete;
};

template <typename T>
class List : private NonCpMvable {
public:
  List() : head_{nullptr} {}

  std::size_t nm() const {
    std::size_t e_nm = 0;
    for (Node *cursor = head_; cursor; cursor = cursor->next) {
      e_nm++;
    }
    return e_nm;
  }

  List& push_front(T value) {
    head_ = new Node{std::move(value), head_};
    return *this;
  }

  ~List() {
    Node *cursor = head_;
    while (cursor) {
      auto waste = cursor;
      cursor = cursor->next;
      delete waste;
    }
  }

  friend std::ostream& operator<<(std::ostream &os, const List &l) {
    for (Node *cursor = l.head_; cursor; cursor = cursor->next) {
      os << cursor->value << "\0 "[!!cursor->next];
    }
    return os;
  }
private:
  struct Node {
    T value;
    Node *next;
  };
private:
  Node *head_;
};

//------

// template <>
// class List<void*> : private NonCpMvable {
// public:
//   List() : head_{nullptr} {}
//   std::size_t nm() const;
//   List<void*>& push_front(void *value);

//   ~List() {
//     Node *cursor = head_;
//     while (cursor) {
//       auto waste = cursor;
//       cursor = cursor->next;
//       delete waste;
//     }
//   }
// private:
//   struct Node {
//     void *value;
//     Node *next;
//   };
// private:
//   Node *head_;
// };

// std::size_t List<void*>::nm() const {
//   std::size_t e_nm = 0;
//   for (Node *cursor = head_; cursor; cursor = cursor->next) {
//     e_nm++;
//   }
//   return e_nm;
// }

// List<void*>& List<void*>::push_front(void *value) {
//   head_ = new Node{value, head_};
//   return *this;
// }

// template <typename T>
// class List<T*> : private NonCpMvable {
// public:
//   std::size_t nm() const { return void_list_.nm(); }

//   List& push_front(T* value) {
//     void_list_.push_front(value);
//     return *this;
//   }

// private:
//   List<void*> void_list_;
// };

int main(int, char**) {
  //List<int> li;
  //std::cout << li.push_front(1).push_front(2).push_front(3) << std::endl;

  int i = 0;
  List<int> li;
  li.nm();
  li.push_front(i);
  List<int *> lip;
  lip.nm();
  lip.push_front(&i);
  List<void*> lvp;
  lvp.nm();
  lvp.push_front(&i);
  double d = 0;
  List<double*> ldp;
  ldp.nm();
  ldp.push_front(&d);
  List<char*> lcp;
  char c = 0;
  lcp.nm();
  lcp.push_front(&c);
  List<int **> lipp;
}
