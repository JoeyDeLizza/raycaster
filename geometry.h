#ifndef GEOMETRY_H
#define GEOMETRY_H
#include "point.h"
#include "vec2.h"

class paraLine {
 public:
 paraLine(vec2 _o, vec2 _d) : o(_o), d(_d) {}

  i_point p(float t);
 private:
  vec2 o, d;
};

#endif
