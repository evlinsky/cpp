#include <string>
#include <map>
#include <iostream>
#include <cstdio>
#include <cassert>

#include "matrix.h"

typedef std::map<std::string, Matrix*> var_storage;

int main(int, char **) {
  std::string cmd, arg1, arg2;
  var_storage vars;

  while (std::cin) {
    std::cin >> cmd;
    if (cmd == "exit") {
      break;
    } else if (cmd == "init") {
      std::size_t rows, cols;
      std::cin >> arg1 >> rows >> cols;
      assert(!vars.count(arg1) && "Already created var");
      vars[arg1] = new Matrix(rows, cols);
    } else if (cmd == "#") {
      std::cin >> arg1;
      assert(vars.count(arg1) && "Unknows var");
      std::cout << vars[arg1]->get_rows() << " ";
      std::cout << vars[arg1]->get_cols() << std::endl;
    } else if (cmd == "get") {
      std::size_t i, j;
      std::cin >> arg1 >> i >> j;
      assert(vars.count(arg1) && "Unknows var");
      std::cout << vars[arg1]->get(i, j) << std::endl;
    } else if (cmd == "set") {
      std::size_t i, j;
      int v;
      std::cin >> arg1 >> i >> j >> v;
      assert(vars.count(arg1) && "Unknows var");
      vars[arg1]->set(i, j, v);
    } else if (cmd == "print") {
      std::cin >> arg1;
      assert(vars.count(arg1) && "Unknows var");
      vars[arg1]->print(stdout);
    } else if (cmd == "cp_init") {
      std::cin >> arg1 >> arg2;
      assert(!vars.count(arg1) && "Already created var");
      assert(vars.count(arg2) && "Unknows var");
      vars[arg1] = new Matrix(*vars[arg2]);
    } else if (cmd == "=") {
      std::cin >> arg1 >> arg2;
      assert(vars.count(arg2) && "Unknows var");
      if (vars.count(arg1) == 0) {
        vars[arg1] = new Matrix(0, 0);
      }
      *vars[arg1] = *vars[arg2];
    } else if (cmd == "==") {
      std::cin >> arg1 >> arg2;
      assert(vars.count(arg1) && "Unknows var");
      assert(vars.count(arg2) && "Unknows var");
      std::cout << (*vars[arg1] == *vars[arg2]) << std::endl;
    } else if (cmd == "!=") {
      std::cin >> arg1 >> arg2;
      assert(vars.count(arg1) && "Unknows var");
      assert(vars.count(arg2) && "Unknows var");
      std::cout << (*vars[arg1] != *vars[arg2]) << std::endl;
    } else if (cmd == "+=") {
      std::cin >> arg1 >> arg2;
      assert(vars.count(arg1) && "Unknows var");
      assert(vars.count(arg2) && "Unknows var");
      *vars[arg1] += *vars[arg2];
    } else if (cmd == "-=") {
      std::cin >> arg1 >> arg2;
      assert(vars.count(arg1) && "Unknows var");
      assert(vars.count(arg2) && "Unknows var");
      *vars[arg1] -= *vars[arg2];
    } else if (cmd == "*=") {
      std::cin >> arg1 >> arg2;
      assert(vars.count(arg1) && "Unknows var");
      assert(vars.count(arg2) && "Unknows var");
      *vars[arg1] *= *vars[arg2];
     } else if (cmd == "+") {
      std::cin >> arg1 >> arg2;
      assert(vars.count(arg1) && "Unknows var");
      assert(vars.count(arg2) && "Unknows var");
      (*vars[arg1] + *vars[arg2]).print(stdout);
    } else if (cmd == "-") {
      std::cin >> arg1 >> arg2;
      assert(vars.count(arg1) && "Unknows var");
      assert(vars.count(arg2) && "Unknows var");
      (*vars[arg1] - *vars[arg2]).print(stdout);
    } else if (cmd == "*") {
      std::cin >> arg1 >> arg2;
      assert(vars.count(arg1) && "Unknows var");
      assert(vars.count(arg2) && "Unknows var");
      (*vars[arg1] * *vars[arg2]).print(stdout);
    }
  }

  for (var_storage::iterator it = vars.begin(); it != vars.end(); ++it) {
    delete it->second;
  }
}
