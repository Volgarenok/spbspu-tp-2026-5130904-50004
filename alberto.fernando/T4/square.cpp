#include "square.hpp"
#include <stdexcept>

namespace alberto {

Square::Square(const point_t& center, double side)
  : center_(center), side_(side)
{
  if (side <= 0.0) {
    throw std::invalid_argument("Square: side must be positive");
  }
}

double Square::getArea() const
{
  return side_ * side_;
}

rectangle_t Square::getFrameRect() const
{
  return { side_, side_, center_ };
}

void Square::move(const point_t& dest)
{
  center_ = dest;
}

void Square::move(double dx, double dy)
{
  center_.x += dx;
  center_.y += dy;
}

void Square::scale(double factor)
{
  if (factor <= 0.0) {
    throw std::invalid_argument("Square::scale: factor must be positive");
  }
  side_ *= factor;
}

}
