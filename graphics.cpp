#include <cstdint>
#include <vector>
#include "graphics.h"
#include <iostream>
#include <algorithm>
#include <cmath>
#include <climits>
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


i_point lineLineIntersection(i_point a, i_point b, i_point c, i_point d) {
  double a1 = b.y - a.y;
  double b1 = a.x - b.x;
  double c1 = a1*(a.x) + b1*(a.y);
  
  // Line CD represented as a2x + b2y = c2
  double a2 = d.y - c.y;
  double b2 = c.x - d.x;
  double c2 = a2*(c.x)+ b2*(c.y);
  
  double determinant = a1*b2 - a2*b1;
  
  if (determinant == 0)
    {
      // The lines are parallel. This is simplified
      // by returning a pair of FLT_MAX
      return i_point(INT_MAX, INT_MAX);
    }
  else
    {
      double x = (b2*c1 - b1*c2)/determinant;
      double y = (a1*c2 - a2*c1)/determinant;
      return i_point(x, y);
    }
}

//lineseg splice_seg(lineseg s) {
// // Create a function to do this
//  vec2 l0 = vec2(s.p0.x, .p0.y);
//  l0 = c.global_to_local(l0);
//  double x0;
//  std::cout << "calcing angle" << "\n";
//  std::cout << l0.get_x() << "\n";
//  std::cout << l0.get_y()<< "\n";
//  std::cout << calculate_angle(l0) << "\n";
//  double ang1 = calculate_angle(l0);
//  
//  if(calculate_angle(l0) < 0) {
//    x0 = 0;
//  }
//
//    if(calculate_angle(l0) < 0 && l0.get_x() < 0) {
//    x0 = 511;
//  }
//    if(calculate_angle(l0) >= 3*PI/4)
//      x0 = 511;
//    if(calculate_angle(l0) <= PI/4)
//      x0 = 0;
//
//  // Create a function to do this
//  vec2 l1 = vec2(p1.x, p1.y);
//  l1 = c.global_to_local(l1);
//  double x1;
//  std::cout << "calcing angle" << "\n";
//  std::cout << l1.get_x() << "\n";
//  std::cout << l1.get_y()<< "\n";
//  std::cout << calculate_angle(l1) << "\n";
//  x1 = round(lin_interp(calculate_angle(l1), PI/4, 3*PI/4, 0, 511));
//  if(calculate_angle(l1) < 0 && l1.get_x() > 0) {
//    x1 = 0;
//  }
//
//    if(calculate_angle(l1) < 0 && l1.get_x() < 0) {
//    x1 = 511;
//  }
//    if(calculate_angle(l1) > 3*PI/4)
//      x1 = 511;
//    if(calculate_angle(l1) <= PI/4)
//      x1 = 0
  

std::vector<lineseg> sort_segs(std::vector<lineseg> segs, coord c) {
  std::vector<lineseg> local_seg;
  std::vector<lineseg> sorted_segs;
  for (auto s : segs) {
    local_seg.push_back(c.global_to_local(s));
  }
  std::sort(local_seg.begin(), local_seg.end());
  for (auto s : local_seg) {
    sorted_segs.push_back(c.local_to_global(s));
  }

  return sorted_segs;
}

std::vector<lineseg> process_segs(std::vector<lineseg> segs, coord c) {
  std::vector<lineseg> columns;
  std::vector<lineseg> sorted_segs = sort_segs(segs, c);
  for (auto s : sorted_segs) {
    process_seg(s, c, columns);

  }
  return columns;
}

void process_seg(lineseg s, coord c, std::vector<lineseg> &cols) {
  
  lineseg local = c.global_to_local(s);
  lineseg x = x_to_screenspace(s.p0, s.p1, c, s.color);
  vec2 local_p1 = c.point_to_vector(s.p0);
  vec2 local_p2 = c.point_to_vector(s.p1);
  local_p1 = c.global_to_local(local_p1);
  local_p2 = c.global_to_local(local_p2);


  // sorted x coordinates
  int begin = std::min(x.p0.x, x.p1.x);
  int end = std::max(x.p0.x, x.p1.x);
  double z1;
  vec2 left_v;
  (calculate_angle(local_p1) < calculate_angle(local_p2)) ? left_v = local_p1 : left_v = local_p2;
  z1 = left_v.len();
  double z2;
  vec2 right_v;
  (calculate_angle(local_p1) > calculate_angle(local_p2)) ? right_v = local_p1 : right_v = local_p2;
  z2 = right_v.len();
  double h1 = left_v.len();
  double h2 = right_v.len();
  h1 = 512 * (30/h1);
  h2 = 512 * (30/h2);
  if (calculate_angle(local_p1) < PI/4 && (calculate_angle(local_p2) < 0 || calculate_angle(local_p2) > (3*PI/4))) {
      return;
    }

  // Handle angles extending past fov on the left
   if(calculate_angle(left_v) < PI/4) {
    h1 = lin_interp(PI/4, calculate_angle(left_v), calculate_angle(right_v), left_v.get_y(), right_v.get_y()) ;
   
       vec2 angle = vec2(cos(PI/4) , sin(PI/4) );
       h1 = left_v.proj((PI/4)-calculate_angle(left_v), (angle));
       vec2 p = angle.mul(h1);
       h1 = p.len();

     h1 = 512 * (30/h1);
     }

   // Handle angles in the bottom left quad
   if(calculate_angle(left_v) <0 && calculate_angle(left_v) > -PI/2) {
       vec2 angle = vec2(cos(PI/4) , sin(PI/4) );
       h1 = left_v.proj((PI/4)-calculate_angle(left_v), (angle));
       vec2 p = angle.mul(h1);
   

       h1 = p.len();
       h1 = 512 * (30/h1);

   }

   // Handle angles going past fov on the right
   if(calculate_angle(right_v) > 3*PI/4) {
    h2 = lin_interp(3*PI/4, calculate_angle(left_v), calculate_angle(right_v), left_v.get_y(), right_v.get_y()) ;
       vec2 angle = vec2(cos(3*PI/4) , sin(3*PI/4) );
       h2 = right_v.proj(calculate_angle(right_v)-(3*PI/4), (angle));
       vec2 p = angle.mul(h2);
       h2 = p.len();
     h2 = 512 * (30/h2);
     }

   // If angle is the bottom right quad, project it
     if(calculate_angle(right_v) < -PI/2 && calculate_angle(right_v) > -PI){
       //   std::cout << "Bottom right quad\n";
       vec2 angle = vec2(cos(3*PI/4) , sin(3*PI/4) );
       h2 = right_v.proj(calculate_angle(right_v)-(3*PI/4), (angle));
       vec2 p = angle.mul(h2);

       h2 = lin_interp(3*PI/4, calculate_angle(left_v), (2*PI + calculate_angle(right_v)), left_v.get_y(), right_v.get_y()) ;
       h2 = p.len();
       h2 = 512 * (30/h2);
     }

  if(calculate_angle(left_v) < -PI/2) {
    double temp;
    temp = h2;
    h2 = h1;
    h1 = temp;
  }


  for(int i = begin; i <= end; i++) {

  // linear interpolate height

    if (i >= 0 && i < 512) {
      double height = lin_interp(i, begin, end, h1, h2);
      if (height > 511)
	height = 510;
      double y1 = 512/2 - height /2;
      double y2 = 512/2 + height /2;
      if (y1 < 0 || y1 > 511)
	y1=0;
      if(y2 < 0 || y2 > 511)
	y2=0;
      cols.push_back(lineseg(i_point(i, (round(y1))), i_point(i, (round(y2))), x.color));
    }
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
  x0 = round(lin_interp(calculate_angle(l0), PI/4, 3*PI/4, 0, 511));
  if(calculate_angle(l0) < 0 && l0.get_x() > 0) {
    x0 = 0;
  }

    if(calculate_angle(l0) < 0 && l0.get_x() < 0) {
    x0 = 511;
  }
    if(calculate_angle(l0) >= 3*PI/4)
      x0 = 511;
    if(calculate_angle(l0) <= PI/4 && calculate_angle(l0) > -PI/2)
      x0 = 0;

  // Create a function to do this
  vec2 l1 = vec2(p1.x, p1.y);
  l1 = c.global_to_local(l1);
  double x1;
  x1 = round(lin_interp(calculate_angle(l1), PI/4, 3*PI/4, 0, 511));
  if(calculate_angle(l1) < 0 && l1.get_x() > 0) {
    x1 = 0;
  }

    if(calculate_angle(l1) < 0 && l1.get_x() < 0) {
    x1 = 511;
  }
    if(calculate_angle(l1) > 3*PI/4)
      x1 = 511;
    if(calculate_angle(l1) < -PI/2 && calculate_angle(l1) > -PI)
      x1 = 511;
    if(calculate_angle(l1) <= PI/4 && calculate_angle(l1) > -PI/2)
      x1 = 0;

    return lineseg(i_point(std::min(x0, x1), 512/2), i_point(std::max(x0 ,x1), 512/2), color);
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
  Uint32 *tp = (Uint32*) s->pixels+((y*512) + x);
  *tp = color;


}


bool check_pixel(SDL_Surface* s, void* pixels, const i_point p) {
  return check_pixel(s, pixels, p.x, p.y);
    }

bool check_pixel(SDL_Surface* s, void* pixels, const int x, const int y) {
    Uint32 *tp = (Uint32*) s->pixels+((y*512) + x);
    if(*tp != 0) {
      return true;
    } else {
      return false;
    }
  }

  
void draw_rectangle(const int x, const int y, const int img_width, const int img_height, const int rect_width,
                    const int rect_height, const uint32_t c, std::vector<uint32_t> &framebuffer) {
   for(int i = y; i < rect_height+y; i++) {
    for(int j = x; j < rect_width+x; j++) {
      framebuffer[j + i*img_width] = c;
    }
  }
}
