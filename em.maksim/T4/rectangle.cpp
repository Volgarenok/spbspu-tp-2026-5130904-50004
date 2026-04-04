#include "rectangle.hpp"

#include <cmath>
#include <stdexcept>

namespace em {

Rectangle::Rectangle(point_t center, double width, double height)
  : center_{center}
{
  if (width <= 0.0 || height <= 0.0) {
    throw std::invalid_argument("Invalid rectangle dimensions");
  }
  width_ = width;
  height_ = height;
}

double Rectangle::getArea() const
{
  return width_ * height_;
}

rectangle_t Rectangle::getFrameRect() const
{
  return {width_, height_, center_};
}

void Rectangle::move(point_t dest)
{
  center_ = dest;
}

void Rectangle::move(double dx, double dy)
{
  center_.x_ += dx;
  center_.y_ += dy;
}

void Rectangle::scale(double factor)
{
  width_ *= factor;
  height_ *= factor;
}

}
