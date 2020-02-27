#ifndef UNI_PTR_H
#define UNI_PTR_H

template <typename T>
class uni_ptr {
public:
  // ctor(T*)
  // T* release()
  // void reset(T* ptr = nullptr)
  // T* operator->()
  // T& operator*()
  // T* get()
  // operator bool
private:
  T *data_;
};


#endif // UNI_PTR_H
