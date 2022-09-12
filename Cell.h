#include <cstdint>
#include <vector>
class Cell {
 public:
  int height = 32, width = 32;
  std::vector<uint32_t> pixels;

 Cell(uint32_t c) : pixels(height*width)  {fillColor(c);}
  void fillColor(uint32_t c);
  static int getWidth() {return 32;}
  static int getHeight() {return 32;}
};
