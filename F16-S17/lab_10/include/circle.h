#pragma once

#include "figure.h"

class Circle : public Figure {
  public:
    Circle(int id, int x, int y, int radius, const char* label);

    ...
};
