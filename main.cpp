#include <iostream>
#include <fstream>
#include <ostream>
#include <sys/types.h>
#include <vector>
#include <cstdint>
#include <cassert>


uint32_t pack_color(const uint8_t r, const uint8_t g, const uint8_t b,
                    const uint8_t a = 255);
void unpack_color(uint32_t c, const uint8_t &r, const uint8_t &g,
                  const uint8_t &b, const uint8_t &a);
void drop_ppm_image(const std::string filename, const std::vector<uint32_t> pixels, int h, int w);

int main(int argc, char **argv) {
  int h = 512;
  int w = 512;

  uint8_t a;
  std::vector<uint32_t> pixels(h*w, 255);
  for(int i = 0; i < h; i++) {
    for(int j = 0; j < w; j++) {
    uint8_t r, g, b;
    r = 255*i/(float)w;
    g = 255*j/(float)h;
    b = 0;
    pixels[i+j*w] = pack_color(r, g, b, a);
    }
  }
  drop_ppm_image("image.ppm", pixels, h, w);
  return 0;
}

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
  std::fstream file = std::fstream("out.ppm", std::fstream::out | std::fstream::binary);

  file << "P6\n" << h << " " << w << "\n255\n";
  

  for(int i = 0; i < h*w; i++) {
      uint8_t r, g, b, a;
      unpack_color(pixels.at(i), r, g, b, a);
      file << static_cast<char>(r) << static_cast<char>(g) << static_cast<char>(b);
  }
  file.close();
}


  
