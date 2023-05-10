#include <cstdint>
#include <vector>
#include "graphics.h"


void draw_pixel(SDL_Surface* surface, int x, int y) {
  
  SDL_UnlockSurface(surface);
  
  set_pixel(surface->pixels, 0xFFFFFFFF, 512/2, 0);
  SDL_LockSurface(surface);
}
  
void set_pixel(void* pixels, const uint32_t color, const int x, const int y) {
  SDL_memset(pixels+((y*512) + x) * 4, 0xFFFFFFFF, 4);

}
  
void draw_rectangle(const int x, const int y, const int img_width, const int img_height, const int rect_width,
                    const int rect_height, const uint32_t c, std::vector<uint32_t> &framebuffer) {
   for(int i = y; i < rect_height+y; i++) {
    for(int j = x; j < rect_width+x; j++) {
      framebuffer[j + i*img_width] = c;
    }
  }
}
