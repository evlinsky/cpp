#include "shared_ptr.h"

#include <iostream>
#include <cassert>
#include <string>
#include <map>

Matrix* make_matrix(int seed) {
    const size_t n = 2;
    Matrix* res = new Matrix(n, n);

    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < n; ++j) {
            res->set(i, j, seed + i * n + j);
        }
    }

    return res;
}

shared_ptr make_shared(int seed) {
    return shared_ptr(make_matrix(seed));
}

void test_empty() {
    shared_ptr ptr;
    assert(ptr.isNull());
    assert(ptr.ptr() == 0);
}

void test_simple() {
    Matrix* m = make_matrix(1);
    Matrix* ref = make_matrix(1);
    shared_ptr ptr(m);

    assert(!ptr.isNull());
    assert(ptr.ptr() == m);
    assert(*ptr.ptr() == *ref);
    delete ref;
}

void test_operators() {
    Matrix* ref = make_matrix(1);
    shared_ptr ptr = make_shared(1);
    
    assert(*ptr == *ref);
    assert(ptr->get_rows() == 2);
    assert(ptr->get_cols() == 2);
    assert((*ptr).get(0, 0) == 1);

    delete ref;
}

void test_assignment() {
    shared_ptr p1 = make_shared(1);
    shared_ptr p2 = make_shared(2);

    assert(*p1 == *make_shared(1));
    assert(*p2 == *make_shared(2));
    p1 = p2;
    assert(*p1 == *make_shared(2));
    assert(*p2 == *make_shared(2));
    p2 = p2;
    assert(*p2 == *make_shared(2));
}

void test_swap() {
    shared_ptr p1 = make_shared(1);
    shared_ptr p2 = make_shared(2);

    std::swap(p1, p2);
    assert(*p1 == *make_shared(2));
    assert(*p2 == *make_shared(1));

    std::swap(p1, p1);
    assert(*p1 == *make_shared(2));
}

void test_reset() {
    shared_ptr p1 = make_shared(1);
    Matrix* m = make_matrix(2);

    p1.reset(m);
    assert(p1.ptr() == m);
    assert(*p1 == *make_shared(2));
    p1.reset();
    assert(p1.isNull());
    assert(p1.ptr() == 0);
}

void test_shared() {
    Matrix* ref = make_matrix(1);
    shared_ptr p1(ref);
    shared_ptr p2(p1);

    assert(p1.ptr() == ref);
    assert(p2.ptr() == ref);
    assert(*p1 == *make_shared(1));
    assert(*p2 == *make_shared(1));
    p1.reset();
    assert(p1.isNull());
    assert(!p2.isNull());
    assert(p2.ptr() == ref);
    assert(*p2 == *make_shared(1));
}

void test_shared_swap() {
    shared_ptr a(make_matrix(1));
    shared_ptr a1(a);
    assert(*a == *make_shared(1));
    
    shared_ptr a2;
    a2 = a;
    assert(*a2 == *make_shared(1));

    shared_ptr b(make_matrix(6));
    shared_ptr b1;
    b1 = b;
    assert(*b1 == *make_shared(6));

    shared_ptr b2(b1);
    assert(*b2 == *make_shared(6));
    
    std::swap(a, b);
    assert(*a == *make_shared(6));
    assert(*b == *make_shared(1));

    std::swap(a, b1);
    assert(*a == *make_shared(6));
    assert(*b1 == *make_shared(6));

    std::swap(a, b);
    assert(*a == *make_shared(1));
    assert(*b == *make_shared(6));

    std::swap(a1, b1);
    assert(*a1 == *make_shared(6));
    assert(*b1 == *make_shared(1));

    std::swap(a1, b1);
    std::swap(a2, b2);
    assert(*a2 == *make_shared(6));
    assert(*b2 == *make_shared(1));
}

void test_many() {
    shared_ptr p;
    p = make_shared(7);
    shared_ptr p1(p);
    shared_ptr p2(p1);
    shared_ptr p3(p2);
    shared_ptr p4(p);
    shared_ptr p5(p1);
    shared_ptr p6(p1);
    shared_ptr p7(p3);
    shared_ptr p8(p7);
    shared_ptr p9(p5);
    p7.reset();
    shared_ptr p10(p7);
    shared_ptr p11(p6);
    shared_ptr p12(p1);
    shared_ptr p13(p2);
    p13.reset(make_matrix(12));
    shared_ptr p14(p3);
    shared_ptr p15(p13);
    shared_ptr p16(p12);
    shared_ptr p17(p15); 
}

typedef void (*test_function)();
typedef std::map<std::string, test_function> test_map;

void init_test_map(test_map& m) {
    m["test_empty"] = test_empty;
    m["test_simple"] = test_simple;
    m["test_operators"] = test_operators;
    m["test_assignment"] = test_assignment;
    m["test_swap"] = test_swap;
    m["test_reset"] = test_reset;
    m["test_shared"] = test_shared;
    m["test_shared_swap"] = test_shared_swap;
    m["test_many"] = test_many;
}

void run_all(const test_map& m) {
    for (test_map::const_iterator it = m.begin(); it != m.end(); ++it) {
        it->second();
    }
}

int main(int argc, char* argv[]) {
    test_map tests;
    init_test_map(tests);

    if (argc < 2 || 
        tests.find(argv[1]) == tests.end()) {
        run_all(tests);
    }
    else {
        tests[argv[1]]();
    }

    std::cout << "OK" << std::endl;

    return 0;
}
