#include "Cell.h"
#include <cstdint>
#include <vector>
#include "graphics.h"

class Map {
  int width, height;
  std::vector<Cell> cells;
 public:
  
 Map(std::vector<Cell> c, int w, int h) : width(w), height(h), cells(c) {}
  
  void drawMap(std::vector<uint32_t> &framebuffer) {
    for(int i = 0; i < width; i++) {
      for(int j = 0; j < height; j++) {
      }
    }
  }

  void drawCell(int x, int y, std::vector<uint32_t> &framebuffer, Cell cell) {

    //  for(int i = x*Cell::getWidth(); i < Cell::getWidth()+x; i++) {
    //for(int j = y*Cell::getHeight(); j < Cell::getHeight()+y; j++) {
    // framebuffer[i + j*Cell::getWidth()] = cell.pixels[i-x + (j-y)*Cell::getWidth()];
    //}
    draw_rectangle(x*Cell::getWidth(), y*Cell::getHeight(), width*Cell::getWidth(), height*Cell::getHeight(), Cell::getWidth(), Cell::getHeight(), cell.pixels.at(0), framebuffer);  
   }
  
  
};


