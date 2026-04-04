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

}
