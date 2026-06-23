#include "square.hpp"

#include <cmath>
#include <stdexcept>

namespace em {

Square::Square(point_t center, double side)
  : center_{center}
{
  if (side <= 0.0) {
    throw std::invalid_argument("Invalid square side");
  }
  side_ = side;
}

double Square::getArea() const
{
  return side_ * side_;
}

rectangle_t Square::getFrameRect() const
{
  return {side_, side_, center_};
}

void Square::move(point_t dest)
{
  center_ = dest;
}

void Square::move(double dx, double dy)
{
  center_.x_ += dx;
  center_.y_ += dy;
}

void Square::scale(double factor)
{
  side_ *= factor;
}

}
