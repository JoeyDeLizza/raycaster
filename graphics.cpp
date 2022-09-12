#include <cstdint>
#include <vector>
#include "graphics.h"

void draw_rectangle(const int x, const int y, const int img_width, const int img_height, const int rect_width,
                    const int rect_height, const uint32_t c, std::vector<uint32_t> &framebuffer) {
   for(int i = y; i < rect_height+y; i++) {
    for(int j = x; j < rect_width+x; j++) {
      framebuffer[j + i*img_width] = c;
    }
  }
}
