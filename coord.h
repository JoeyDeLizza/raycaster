#include "vec2.h"

class coord
{
public:
  coord(vec2 _p, vec2 _u, vec2 _v) : p(_p), u(_u), v(_v) {}

  vec2 local_to_global(vec2 u);

  vec2 global_to_local(vec2 x);


  virtual ~coord() {}

private:

  vec2 p, u, v;

  vec2 u_global_pos();

  vec2 v_global_pos();
  
};
