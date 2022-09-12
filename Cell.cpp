#include "Cell.h"
#include <cstdint>

void Cell::fillColor(uint32_t c) {
  for(int i = 0; i < height*width-1; i++) {
    pixels[i] = c;
  }
}
