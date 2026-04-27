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

aydogan::rectangle_t aydogan::Rectangle::getFrameRect() const
{
  return rectangle_t(width_, height_, center_);
}

void aydogan::Rectangle::move(const point_t& point)
{
  center_ = point;
}

void aydogan::Rectangle::move(double dx, double dy)
{
  center_.x_ += dx;
  center_.y_ += dy;
}

void aydogan::Rectangle::scale(double coefficient)
{
  if (coefficient <= 0.0)
  {
    throw std::invalid_argument("Invalid scale coefficient");
  }

  width_ *= coefficient;
  height_ *= coefficient;
}
