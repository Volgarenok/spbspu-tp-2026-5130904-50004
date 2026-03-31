#include "rectangle.hpp"

double zinoviev::Rectangle::getArea() const
{
  return width_ * height_;
}

zinoviev::rectangle_t zinoviev::Rectangle::getFrameRect() const
{
  return rectangle_t(center_, width_, height_);
}

void zinoviev::Rectangle::move(const point_t& newPos)
{
  center_ = newPos;
}

void zinoviev::Rectangle::move(double dx, double dy)
{
  center_.x += dx;
  center_.y += dy;
}

void zinoviev::Rectangle::scale(double k)
{
  if (k <= 0.0)
    throw std::logic_error("Coefficient must be positive");

  width_ *= k;
  height_ *= k;
}
