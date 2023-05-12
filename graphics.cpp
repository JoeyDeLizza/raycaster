#include <cstdint>
#include <vector>
#include "graphics.h"
#include <iostream>

void draw_screen(SDL_Surface* s, SDL_Texture* t, SDL_Renderer* r) {
  
  SDL_UpdateTexture(t, NULL, s->pixels, s->pitch);
  SDL_SetRenderDrawColor(r, 255, 0, 255, 255);
  SDL_RenderClear(r);
  SDL_RenderCopy(r, t, NULL, NULL);
  SDL_RenderPresent(r);
  
}

void line(int x0, int y0, int x1, int y1, SDL_Surface* s, Uint32 color) {
  std::cout << "Starting line func" << std::endl;
  std::cout << x0 << y0 << x1 << y1 << std::endl;
  if (std::abs(y1 - y0) < std::abs(x1 - x0)) {
    if (x0 > x1) {
      plotLineLow(x1, y1, x0, y0, s, color);
    } else {
      plotLineLow(x0, y0, x1, y1, s, color);
    }
  } else {
    if (y0 > y1) {
       plotLineHigh(x1, y1, x0, y0, s, color);
    } else {
      plotLineHigh(x0, y0, x1, y1, s, color);
    }
  }
  
}

void plotLineHigh(int x0, int y0, int x1, int y1, SDL_Surface* s, Uint32 color) {
  int dx = x1 - x0;
  int dy = y1 - y0;
  int xi = 1;
  if (dx < 0) {
    xi = -1;
    dx = -dx;
  }

  int D = (2* dx) - dy;
  int x = x0;
  for(int y = y0; y <=y1; y++) {
    std::cout << "Changing Pixel" << std::endl;
    std::cout << "In for loop" << std::endl;
    std::cout << y << y0 << std::endl;

    std::cout << x0 << y0 << x1 << y1 << std::endl;
    update_pixel(s, color, x, y);
    if (D > 0) {
      x = x +xi;
      D = D + (2 * (dx - dy));
    } else{
      D = D + 2*dx;
    }
  }
}

void plotLineLow(int x0, int y0, int x1, int y1, SDL_Surface* s, Uint32 color) {
  int dx = x1 - x0;
  int dy = y1 - y0;
  int yi = 1;
  if (dy < 0) {
    yi = -1;
    dy = -dy;
  }

  int D = (2*dy) -dx;
  int y = y0;
  for(int x = x0; x <= x1; x++) {
    
    update_pixel(s, color, x, y);
    if(D > 0) {
      y = y + yi;
      D = D + (2 * (dy -dx));
    } else {
      D = D + 2*dy;
    }
  }
}

void update_pixel(SDL_Surface* surface, Uint32 color, int x, int y) {
  std::cout << "In update Pixel:" << std::endl;
  std::cout << y << std::endl;
  SDL_UnlockSurface(surface);
  
  set_pixel(surface, surface->pixels, color, x, y);
  SDL_LockSurface(surface);
}
// quick and dirty way to set a 32bit argb pixel
void set_pixel(SDL_Surface* s, void* pixels, Uint32 color, int x, int y) {
  //Fix warning about arithmetic on void pointer: could cast it to uint32_t pointer
  //SDL_memset(pixels+((y*512) + x) * 4, color, 32);
  std::cout << "In set Pix" << std::endl;
  std::cout << x << y;
  Uint32 *tp = (Uint32*) s->pixels+((y*512) + x);
  *tp = color;


}
  
void draw_rectangle(const int x, const int y, const int img_width, const int img_height, const int rect_width,
                    const int rect_height, const uint32_t c, std::vector<uint32_t> &framebuffer) {
   for(int i = y; i < rect_height+y; i++) {
    for(int j = x; j < rect_width+x; j++) {
      framebuffer[j + i*img_width] = c;
    }
  }
}
