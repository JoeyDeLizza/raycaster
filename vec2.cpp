// vec2
#include "vec2.h"


vec2 vec2::add(vec2 b) {
  vec2 c = vec2(this->x + b.get_x(), this->y + b.get_y());
  return c;
}

vec2 vec2::mul(double m) {
  return vec2(this->x * m, this->y * m);
}

double vec2::dot(vec2 b) {
  return this->x * b.get_x() + this->y * b.get_y();
}

double vec2::len() {
  return sqrt(this->x * this->x + this->y * this->y);
}

void vec2::operator=(vec2 b) {
  this->x = b.get_x();
  this->y = b.get_y();
}
//vec2 vec2::cross(vec2 b) {
  //  return this->dot(a) 
//
double vec2::get_x() {
  return this->x;
}

double vec2::get_y() {
  return this->y;
}

double vec2::proj(double ang, vec2 b) {
  double a_1 = this->len() * cos(ang);
  return a_1;
}
//
vec2 vec2::operator+(vec2 b) {
  return this->add(b);
}
//
//vec2 vec2::operator-(vec2 b) {
//  
//}
