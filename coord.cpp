//coord.cpp
#include "coord.h"

vec2 coord::local_to_global(vec2 b) {

  return vec2(this->u.mul(b.get_x()) + this->v.mul(b.get_y())) + this->p;
}

vec2 coord::global_to_local(vec2 b) {

  return vec2(this->u.dot(b), this->v.dot(b)) + this->p;
}
