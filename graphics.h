#ifndef GRAPHICS_H
#define GRAPHICS_H
#include <sys/types.h>
#include "/usr/local/include/SDL2/SDL.h"
#include "lineseg.h"
#include "point.h"
#include "coord.h"
#include <vector>

void draw_screen(SDL_Surface* s, SDL_Texture* t, SDL_Renderer* r);

void line(i_point p0, i_point p1, SDL_Surface* s, Uint32 color);

void line(int x0, int y0, int x1, int y1, SDL_Surface* s, Uint32 color);

double lin_interp(double x, double xi, double xi2, double yi, double yi2); 

i_point lineLineIntersection(i_point a, i_point b, i_point c, i_point d);

lineseg splice_seg(lineseg s);

std::vector<lineseg> sort_segs(std::vector<lineseg> segs, coord c);

std::vector<lineseg> process_segs(std::vector<lineseg> segs, coord c);

void process_seg(lineseg s, coord c, std::vector<lineseg> &cols);

// Move this to a better module
double calculate_angle(vec2 u);

lineseg x_to_screenspace(i_point p0, i_point p1, coord c, Uint32 color);

void plotLineHigh(int x0, int y0, int x1, int y1, SDL_Surface* s, Uint32 color);

void plotLineLow(int x0, int y0, int x1, int y1, SDL_Surface* s, Uint32 color);

// Change surface to s in this and cpp for consistency
void update_pixel(SDL_Surface* surface, const Uint32 color, const int x, const int y);

void set_pixel(SDL_Surface* s, void* pixels, const Uint32 color, const int x, const int y);

bool check_pixel(SDL_Surface* s, void* pixels, const i_point p);

bool check_pixel(SDL_Surface* s, void* pixels, const int x, const int y);

void draw_rectangle(const int x, const int y, const int img_width, const int img_height, const int rect_width,
                    const int rect_height, const uint32_t c, std::vector<uint32_t> &framebuffer);

#endif
