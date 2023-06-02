//coord.cpp
#include "coord.h"

vec2 coord::local_to_global(vec2 b) {

  return vec2(this->u.mul(b.get_x()) + this->v.mul(b.get_y())) + this->p;
}

vec2 coord::global_to_local(vec2 b) {
  return vec2(this->u.dot(b), this->v.dot(b)) + vec2(this->u.dot(this->p), this->v.dot(this->p)).mul(-1);
}

vec2 coord::point_to_vector(i_point p) {

  return vec2(p.x, p.y);
}

i_point coord::vector_to_point(vec2 u) {

  return i_point(round(u.get_x()), round(u.get_y()));
}

lineseg coord::global_to_local(lineseg s) {

  vec2 u = vec2(s.p0);
  vec2 v = vec2(s.p1);

  vec2 local_u = global_to_local(u);
  vec2 local_v = global_to_local(v);

  return lineseg(vector_to_point(local_u), vector_to_point(local_v), s.color);
}

lineseg coord::local_to_global(lineseg s) {

  vec2 u = vec2(s.p0);
  vec2 v = vec2(s.p1);

  vec2 global_u = local_to_global(u);
  vec2 global_v = local_to_global(v);

  return lineseg(vector_to_point(global_u), vector_to_point(global_v), s.color);
}

