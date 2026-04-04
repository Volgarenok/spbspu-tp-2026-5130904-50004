#include "utils.hpp"
#include <algorithm>
#include <iostream>

namespace pozdeev {

void scaleRelativeToPoint(
  std::weak_ptr<Shape> shapeWeak,
  const point_t& point,
  double coefficient)
{
  auto shape = shapeWeak.lock();
  if (!shape)
  {
    return;
  }

  rectangle_t frame = shape->getFrameRect();
  point_t oldCenter = frame.pos_;

  double newX = point.x_ + coefficient * (oldCenter.x_ - point.x_);
  double newY = point.y_ + coefficient * (oldCenter.y_ - point.y_);

  shape->move(newX - oldCenter.x_, newY - oldCenter.y_);
  shape->scale(coefficient);
}

}
