#include "square.hpp"
#include <stdexcept>

aydogan::Square::Square(double side, const point_t& center):
  side_(side),
  center_(center)
{
  if (side_ <= 0.0)
  {
    throw std::invalid_argument("Invalid square side");
  }
}

double aydogan::Square::getArea() const
{
  return side_ * side_;
}

aydogan::rectangle_t aydogan::Square::getFrameRect() const
{
  return rectangle_t(side_, side_, center_);
}
