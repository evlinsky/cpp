#pragma once

#include "matrix.h"

class shared_ptr {
  public:
    shared_ptr(Matrix* obj = 0);
    shared_ptr(const shared_ptr& other);
    shared_ptr& operator=(shared_ptr other);
    ~shared_ptr();

    Matrix* ptr() const;
    bool isNull() const;
    void reset(Matrix* obj = 0);

    Matrix* operator->() const;
    Matrix& operator*() const;

  private:
    class Storage {
      public:
        Storage(Matrix* mtx);
        ~Storage();

        void incr();
        void decr();

        int getCounter() const;
        Matrix* getObject() const;

      private:
        Matrix *data_;
        int ref_count_;
    };

  private:
    Storage *storage_;
};
