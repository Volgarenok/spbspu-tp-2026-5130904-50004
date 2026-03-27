#include "Shape.h"

Rectangle::Rectangle(double width, double height, point_t pos):
  rect_(rectangle_t{width, height, pos})
{
}

double Rectangle::getArea() const
{
  return rect_.height_ * rect_.width_;
}

rectangle_t Rectangle::getFrameRect() const
{
  return rect_;
}

void Rectangle::move(point_t new_center)
{
  rect_.pos_ = new_center;
}

void Rectangle::move(double x, double y)
{
  rect_.pos_.x_ += x;
  rect_.pos_.y_ += y;
}

void Rectangle::scale(double k)
{
  rect_.width_ *= k;
  rect_.height_ *= k;
}
