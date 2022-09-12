#include <iostream>
#include <fstream>
#include <ostream>
#include <sys/types.h>
#include <vector>
#include <cstdint>
#include <cassert>
#include "graphics.h"
#include "map.h"


uint32_t pack_color(const uint8_t r, const uint8_t g, const uint8_t b,
                    const uint8_t a = 255);
void unpack_color(uint32_t c, const uint8_t &r, const uint8_t &g,
                  const uint8_t &b, const uint8_t &a);
void drop_ppm_image(const std::string filename,
                    const std::vector<uint32_t> pixels, int h, int w);
void draw_rectangle(const int x, const int y, const int img_width, const int img_height, const int rect_width,
                    const int rect_height, const uint32_t c, std::vector<uint32_t> &framebuffer);


int main(int argc, char **argv) {
  int h = 512;
  int w = 512;

  uint8_t a;
  std::vector<uint32_t> framebuffer(h*w, 255);
  for(int i = 0; i < h; i++) {
    for(int j = 0; j < w; j++) {
    uint8_t r, g, b;
    r = 255*i/(float)w;
    g = 255*j/(float)h;
    b = 0;
    framebuffer[i+j*w] = pack_color(r, g, b, a);
    }
  }
  Cell white = Cell(pack_color(255, 255, 255));
  std::vector<Cell> cells(16*16, white);
  Map m = Map(cells, 16, 16);
  uint32_t c = pack_color(255,255,255);
  draw_rectangle(50,50,h,w,5,5,c, framebuffer);
  //map m = map(cells, 16, 16);
  drop_ppm_image("image.ppm", framebuffer, h, w);
  m.drawCell(0,0, framebuffer, white);
  drop_ppm_image("image2.ppm", framebuffer, h, w);
  return 0;
}

//void draw_rectangle(const int x, const int y, const int img_width, const int img_height, const int rect_width, const int rect_height, const uint32_t c, std::vector<uint32_t> &framebuffer) {
//  for(int i = y; i < rect_height+y; i++) {
//    for(int j = x; j < rect_width+x; j++) {
//      framebuffer[j + i*img_width] = c;
//    }
//  }
//}

uint32_t pack_color(const uint8_t r, const uint8_t g, const  uint8_t b, const uint8_t a) {
  return (a << 24) + (b << 16) + (g << 8) + r;
}

void unpack_color(const uint32_t &c,  uint8_t &r,  uint8_t &g,  uint8_t &b,  uint8_t &a) {
  r = (c >> 0) & 255;
  g = (c >> 8) & 255;
  b = (c >> 16) & 255;
  a = (c >> 24) & 255;
}

void drop_ppm_image(const std::string filename, const std::vector<uint32_t> pixels, const int h, const int w) {
  std::fstream file = std::fstream(filename, std::fstream::out | std::fstream::binary);

  file << "P6\n" << h << " " << w << "\n255\n";
  

  for(int i = 0; i < h*w; i++) {
      uint8_t r, g, b, a;
      unpack_color(pixels.at(i), r, g, b, a);
      file << static_cast<char>(r) << static_cast<char>(g) << static_cast<char>(b);
  }
  file.close();
}


  
