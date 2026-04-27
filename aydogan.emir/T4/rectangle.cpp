#include "rectangle.hpp"
#include <stdexcept>

aydogan::Rectangle::Rectangle(double width, double height, const point_t& center):
  width_(width),
  height_(height),
  center_(center)
{
  if (width_ <= 0.0 || height_ <= 0.0)
  {
    throw std::invalid_argument("Invalid rectangle size");
  }
}

double aydogan::Rectangle::getArea() const
{
  return width_ * height_;
}
