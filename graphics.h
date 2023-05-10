#include <sys/types.h>

#include "SDL2/SDL.h"

void draw_pixel(SDL_Surface* surface, int x, int y);

void set_pixel(void* pixels, const uint32_t color, const int x, const int y);

void draw_rectangle(const int x, const int y, const int img_width, const int img_height, const int rect_width,
                    const int rect_height, const uint32_t c, std::vector<uint32_t> &framebuffer);
