//lineseg
#include "lineseg.h"
#include <algorithm>
#include "vec2.h"

bool lineseg::operator<(const lineseg& l) {
  return std::max(abs(this->p0.y), abs(this->p1.y)) > std::max(abs(l.p0.y), abs(l.p1.y));
}
