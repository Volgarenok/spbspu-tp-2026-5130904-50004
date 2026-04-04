#include "rectangle.hpp"
#include <stdexcept>
#include <cmath>

namespace alberto {

Rectangle::Rectangle(const point_t& center, double width, double height)
  : center_(center), width_(width), height_(height)
{
  if (width <= 0.0 || height <= 0.0) {
    throw std::invalid_argument("Rectangle: width and height must be positive");
  }
}

Rectangle::Rectangle(const point_t& bottomLeft, const point_t& topRight)
  : center_({ (bottomLeft.x + topRight.x) / 2.0, (bottomLeft.y + topRight.y) / 2.0 }),
    width_(topRight.x - bottomLeft.x),
    height_(topRight.y - bottomLeft.y)
{
  if (width_ <= 0.0 || height_ <= 0.0) {
    throw std::invalid_argument("Rectangle: topRight must be to the upper-right of bottomLeft");
  }
}

double Rectangle::getArea() const
{
  return width_ * height_;
}

rectangle_t Rectangle::getFrameRect() const
{
  return { width_, height_, center_ };
}

void Rectangle::move(const point_t& dest)
{
  center_ = dest;
}

void Rectangle::move(double dx, double dy)
{
  center_.x += dx;
  center_.y += dy;
}

void Rectangle::scale(double factor)
{
  if (factor <= 0.0) {
    throw std::invalid_argument("Rectangle::scale: factor must be positive");
  }
  width_ *= factor;
  height_ *= factor;
}

}
