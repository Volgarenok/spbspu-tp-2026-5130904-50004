#include "rectangle.hpp"
#include <stdexcept>

namespace aushev
{
  Rectangle::Rectangle(double width, double height, point_t pos):
    width_(width), height_(height), pos_(pos)
  {
    if (width_ <= 0.0 || height_ <= 0.0)
    {
      throw std::invalid_argument("Sizes must be positive");
    }
  }

  double Rectangle::getArea() const
  {
    return width_ * height_;
  }

  rectangle_t Rectangle::getFrameRect() const
  {
    return rectangle_t(width_, height_, pos_);
  }

  void Rectangle::move(const point_t& p)
  {
    pos_ = p;
  }

  void Rectangle::move(double dx, double dy)
  {
    pos_.x_ += dx;
    pos_.y_ += dy;
  }

  void Rectangle::scale(double k)
  {
    if (k <= 0.0)
    {
      throw std::invalid_argument("Scale coefficient must be positive");
    }
    width_ *= k;
    height_ *= k;
  }
}
