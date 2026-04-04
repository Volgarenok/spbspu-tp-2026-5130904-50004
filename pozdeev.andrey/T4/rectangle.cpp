#include "rectangle.hpp"

namespace pozdeev {

Rectangle::Rectangle(double width, double height, const point_t& pos)
  : rect_{width, height, pos}
{}

double Rectangle::getArea() const
{
  return rect_.width_ * rect_.height_;
}

rectangle_t Rectangle::getFrameRect() const
{
  return rect_;
}

void Rectangle::move(double dx, double dy)
{
  rect_.pos_.x_ += dx;
  rect_.pos_.y_ += dy;
}

void Rectangle::move(const point_t& point)
{
  rect_.pos_ = point;
}

void Rectangle::scale(double coefficient)
{
  rect_.width_ *= coefficient;
  rect_.height_ *= coefficient;
}

}
