#include "rectangle.hpp"

#include <stdexcept>

vasilenko::Rectangle::Rectangle(double width, double height, const point_t &pos):
  width_(width),
  height_(height),
  pos_(pos)
{
  if (width_ <= 0.0 || height_ <= 0.0) {
    throw std::invalid_argument("Width and height must be positive");
  }
}

double vasilenko::Rectangle::getArea() const
{
  return width_ * height_;
}

vasilenko::rectangle_t vasilenko::Rectangle::getFrameRect() const
{
  return {width_, height_, pos_};
}

void vasilenko::Rectangle::move(const point_t &point)
{
  pos_ = point;
}

void vasilenko::Rectangle::move(double dx, double dy)
{
  pos_.x += dx;
  pos_.y += dy;
}

void vasilenko::Rectangle::scale(double coefficient)
{
  if (coefficient <= 0.0) {
    throw std::invalid_argument("Scale coefficient must be positive");
  }
  width_ *= coefficient;
  height_ *= coefficient;
}
