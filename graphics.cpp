#include <cstdint>
#include <vector>
#include "graphics.h"
#include <iostream>
#include <algorithm>
#include <cmath>
#define PI 3.14159265

void draw_screen(SDL_Surface* s, SDL_Texture* t, SDL_Renderer* r) {
  
  SDL_UpdateTexture(t, NULL, s->pixels, s->pitch);
  SDL_SetRenderDrawColor(r, 0, 0, 0, 255);
  SDL_RenderClear(r);
  SDL_RenderCopy(r, t, NULL, NULL);
  SDL_RenderPresent(r);
  
}

void line(i_point p0, i_point p1, SDL_Surface* s, Uint32 color) {
  line(p0.x, p0.y, p1.x, p1.y, s, color);
}

void line(int x0, int y0, int x1, int y1, SDL_Surface* s, Uint32 color) {
  //std::cout << "Starting line func" << std::endl;
  //std::cout << x0 << y0 << x1 << y1 << std::endl;
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

double lin_interp(double x, double xi, double xi2, double yi, double yi2) {

  return yi + ( (x - xi) / (xi2 - xi) ) * (yi2 -yi);
}

std::vector<lineseg> sort_segs(std::vector<lineseg> segs, coord c) {
  std::vector<lineseg> local_seg;
  std::vector<lineseg> sorted_segs;
  for (auto s : segs) {
  std::cout << s.p0.x << "," << s.p0.y << "\n";
  std::cout << s.p1.x << "," << s.p1.y << "\n";
    local_seg.push_back(c.global_to_local(s));
  }
  std::sort(local_seg.begin(), local_seg.end());
  for (auto s : local_seg) {
  std::cout << s.p0.x << "," << s.p0.y << "\n";
  std::cout << s.p1.x << "," << s.p1.y << "\n";

    sorted_segs.push_back(c.local_to_global(s));
  }

  for (auto s: sorted_segs) {
    std::cout << s.p0.x << "," << s.p0.y << "\n";
    std::cout << s.p1.x << "," << s.p1.y << "\n";
  }
  return sorted_segs;
}

std::vector<lineseg> process_segs(std::vector<lineseg> segs, coord c) {
  std::vector<lineseg> columns;
  std::vector<lineseg> sorted_segs = sort_segs(segs, c);
  for (auto s : sorted_segs) {
    process_seg(s, c, columns);

    // if (x.p0.x >= 0 && x.p0.x <= 512)
    //   columns.push_back(lineseg(x.p0, x.p0, x.color));
    // if (x.p1.x >= 0 && x.p1.x <= 512)
    //   columns.push_back(lineseg(x.p1, x.p1, x.color));
  }
  return columns;
}

void process_seg(lineseg s, coord c, std::vector<lineseg> &cols) {
  std::cout << "processing lineseg" << "\n";
  std::cout << s.color << "\n";
  std::cout << s.p0.x << "," << s.p0.y << "\n";
  std::cout << s.p1.x << "," << s.p1.y << "\n";
  
  lineseg local = c.global_to_local(s);
  //lineseg x = lineseg(i_point(x_to_screenspace(s.p0, c), 512/2), i_point(x_to_screenspace(s.p1, c), 512/2), s.color); 
  lineseg x = x_to_screenspace(s.p0, s.p1, c, s.color);
  std::cout << x.p0.x << "," << x.p1.x << "\n";
  vec2 local_p1 = c.point_to_vector(s.p0);
  vec2 local_p2 = c.point_to_vector(s.p1);
  local_p1 = c.global_to_local(local_p1);
  local_p2 = c.global_to_local(local_p2);


  int begin = std::min(x.p0.x, x.p1.x);
  int end = std::max(x.p0.x, x.p1.x);
  std::cout << x.p0.x << "\n";
  std::cout << x.p1.x << "\n";
  std::cout << begin << "\n";
  std::cout << end << "\n";
  double z1 = local_p2.len();
  //(local_p1.get_x() < local_p2.get_x()) ? z1 = local_p1.len() : z1 = local_p2.len();

  double z2 = local_p1.len();
  //(local_p1.get_x() > local_p2.get_x()) ? z2 = local_p1.len() : z2 = local_p2.len();


  //std::cout << x_to_screenspace(s.p0, c) << "\n";
  std::cout << "Printing distances:" << "\n";
  std::cout << z1 << "\n";
  std::cout << z2 << "\n";
  std::cout << "Printing Heights" << "\n";
  std::cout << (512/2) - 512 * (50)/z1 << "\n";

  std::cout << (512/2) -512 * (50)/z2 << "\n";


  double x0 = round(lin_interp(calculate_angle(local_p1), PI/4, 3*PI/4, 0, 512));
  double x1 = round(lin_interp(calculate_angle(local_p2), PI/4, 3*PI/4, 0, 512));



  cols.push_back(lineseg(i_point(x.p0.x, (int) (((512/2) - (512*(50/z1))/2))), i_point(x.p1.x, (int) ((512/2) - (512*(50/z2))/2)), 0xFFFFFFFF));

  cols.push_back(lineseg(i_point(x.p0.x, (int) (((512/2) + (512*(50/z1))/2))), i_point(x.p1.x, (int) ((512/2) + (512*(50/z2))/2)), 0xFFFFFFFF));

  for(int i = begin; i < end; i++) {

    //std::cout << x_to_screenspace(s.p1, c) << "\n";
  // linear interpolate height
    double z = lin_interp(i, x0, x1, z2, z1);
    std::cout << "Printing heights" << "\n";
    std::cout << i << "," << z << "\n";
    if (z < 0 || z == 0)
      z = 0;

    if (i >= 0 && i < 512) {
      double height = 512 * (50/z);
      double y1 = 512/2 - height /2;
      double y2 = 512/2 + height /2;
      if (y1 < 0 || y1 > 511)
	y1=0;
      if(y2 < 0 || y2 > 511)
	y2=0;
      cols.push_back(lineseg(i_point(i, round(y1)), i_point(i, round(y2)), x.color));
    }
  if (x.p0.x >= 0 && x.p0.x <= 512) {
    double height = 512 * (50/z1);
    //cols.push_back(lineseg(i_point(x.p0.x, (512 / 2 - height / 2)), i_point(x.p0.x, (512 / 2 + height / 2)) , 0xFFFFFFFF));
  }
  if (x.p1.x >= 0 && x.p1.x <= 512) {
    double height = 512 * (50/z2);
    //cols.push_back(lineseg(i_point(x.p1.x, (512 / 2 - height / 2)), i_point(x.p1.x, (512 / 2 + height / 2)), 0xFFFFFFFF));
  }

  //cols.push_back(lineseg(i_point(x.p0.x, (512/2) - (512*(50/z1))/2), i_point(x.p1.x, (512/2) - (512*(50/z2))/2), 0xFFFFFFFF));
}
}

double calculate_angle(vec2 u) {
  return atan2( (double) u.get_y(), (double) u.get_x() );
}

lineseg x_to_screenspace(i_point p0, i_point p1, coord c, Uint32 color) {

  // Create a function to do this
  vec2 l0 = vec2(p0.x, p0.y);
  l0 = c.global_to_local(l0);
  double x0;
  std::cout << "calcing angle" << "\n";
  std::cout << l0.get_x() << "\n";
  std::cout << l0.get_y()<< "\n";
  std::cout << calculate_angle(l0) << "\n";
  x0 = round(lin_interp(calculate_angle(l0), PI/4, 3*PI/4, 0, 512));
  if(calculate_angle(l0) < 0 && l0.get_x() > 0) {
    x0 = 0;
  }

    if(calculate_angle(l0) < 0 && l0.get_x() < 0) {
    x0 = 511;
  }

  // Create a function to do this
  vec2 l1 = vec2(p1.x, p1.y);
  l1 = c.global_to_local(l1);
  double x1;
  std::cout << "calcing angle" << "\n";
  std::cout << l1.get_x() << "\n";
  std::cout << l1.get_y()<< "\n";
  std::cout << calculate_angle(l1) << "\n";
  x1 = round(lin_interp(calculate_angle(l1), PI/4, 3*PI/4, 0, 512));
  if(calculate_angle(l1) < 0 && l1.get_x() > 0) {
    x1 = 0;
  }

    if(calculate_angle(l1) < 0 && l1.get_x() < 0) {
    x1 = 511;
  }

    return lineseg(i_point(x0, 512/2), i_point(x1, 512/2), color);
    //return round(lin_interp(calculate_angle(l), PI/4, 3*PI/4, 0, 511));
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
    //  std::cout << "Changing Pixel" << std::endl;
    // std::cout << "In for loop" << std::endl;
    //std::cout << y << y0 << std::endl;

    //std::cout << x0 << y0 << x1 << y1 << std::endl;
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
  //std::cout << "In update Pixel:" << std::endl;
  //std::cout << x << y << std::endl;
  SDL_UnlockSurface(surface);
  
  set_pixel(surface, surface->pixels, color, x, y);
  SDL_LockSurface(surface);
}
// quick and dirty way to set a 32bit argb pixel
void set_pixel(SDL_Surface* s, void* pixels, Uint32 color, int x, int y) {
  //Fix warning about arithmetic on void pointer: could cast it to uint32_t pointer
  //SDL_memset(pixels+((y*512) + x) * 4, color, 32);
  //std::cout << "In set Pix" << std::endl;
  //std::cout << x << y;
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
