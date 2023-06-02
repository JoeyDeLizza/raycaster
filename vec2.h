#ifndef VEC2_H
#define VEC2_H

#include <math.h>
#include "point.h"
//2-Dimensional vector

class vec2 {
 public:
 vec2(double _x, double _y) : x(_x), y(_y) {}

  vec2(i_point p) : x(p.x), y(p.y) {}

  vec2() : x(0), y(0) {}

  vec2 add(vec2 b);

  vec2 mul(double m);

  double dot(vec2 b);

  double len();

  double cross();

  double get_x();

  double get_y();

  vec2 operator+(vec2 b);

  vec2 operator-();

  void operator=(vec2 b);
  

 private:
  double x, y;
  double* x_ptr, y_ptr;
};

#endif
