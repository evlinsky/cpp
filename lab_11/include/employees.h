#ifndef __LAB11_EMPLOYEES_H_INCLUDED
#define __LAB11_EMPLOYEES_H_INCLUDED

#include <stdint.h>

class Developer {
public:
  int salary() const {
    int salary = _base_salary;
    if (_has_bonus) { salary += 1000; }
    return salary;
  }
  /* ?? operator>>(??); */
  /* ?? operator<<(??); */
private:
  char *_name;
  int32_t _base_salary;
  bool _has_bonus;
};

class SalesManager {
public:
  int salary() const {
    return _base_salary + _sold_nm * _price * 0.01;
  }
  /* ?? operator>>(??); */
  /* ?? operator<<(??); */
private:
  char *_name;
  int32_t _base_salary;
  int32_t _sold_nm, _price;
};

class EmployeesArray {
public:
  void add(const Employee *e);
  int total_salary() const;
  /* ?? operator>>(??); */
  /* ?? operator<<(??); */
private:
  Employee **_employees;
};

#endif
