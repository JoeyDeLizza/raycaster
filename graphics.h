#include <sys/types.h>

#include "SDL2/SDL.h"

void draw_screen(SDL_Surface* s, SDL_Texture* t, SDL_Renderer* r);

void line(int x0, int y0, int x1, int y1, SDL_Surface* s, Uint32 color);

void plotLineHigh(int x0, int y0, int x1, int y1, SDL_Surface* s, Uint32 color);

void plotLineLow(int x0, int y0, int x1, int y1, SDL_Surface* s, Uint32 color);

// Change surface to s in this and cpp for consistency
void update_pixel(SDL_Surface* surface, const Uint32 color, const int x, const int y);

void set_pixel(SDL_Surface* s, void* pixels, const Uint32 color, const int x, const int y);

void draw_rectangle(const int x, const int y, const int img_width, const int img_height, const int rect_width,
                    const int rect_height, const uint32_t c, std::vector<uint32_t> &framebuffer);
