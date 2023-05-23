// geometry.cpp
#include "geometry.h"
#include <iostream>

i_point paraLine::p(float t) {
  vec2 temp = this->o + (this->d.mul(t));
  return i_point(temp.get_x(), temp.get_y());
}
