#ifndef COORD_H
#define COORD_H
#include "vec2.h"
#include "lineseg.h"

class coord
{
public:
  coord(vec2 _p, vec2 _u, vec2 _v) : p(_p), u(_u), v(_v) {}

  // Generalize converting to and from global and local coordinates
  vec2 local_to_global(vec2 b);

  vec2 global_to_local(vec2 b);

  vec2 point_to_vector(i_point p);

  i_point vector_to_point(vec2 b);
  
  lineseg global_to_local(lineseg s);

  lineseg local_to_global(lineseg s);

  virtual ~coord() {}

private:

  vec2 p, u, v;

  vec2 u_global_pos();

  vec2 v_global_pos();
  
};

#endif
