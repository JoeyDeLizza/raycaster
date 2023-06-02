#ifndef POINT_H
#define POINT_H

#include "point.h"
#include <cstdint>
#include "vec2.h"

class lineseg {
public:
  i_point p0, p1;
  uint32_t color;
  lineseg(i_point _p0, i_point _p1, uint32_t _color)
    : p0(_p0), p1(_p1), color(_color) {}

  bool operator<(const lineseg& l);
};

#endif
