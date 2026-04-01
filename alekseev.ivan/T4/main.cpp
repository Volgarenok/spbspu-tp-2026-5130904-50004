#include "Shape.h"
#include <memory>
#include <iostream>

namespace alekseev {
  void scale_pivot(std::weak_ptr< iShape > shape, point_t pivot, double k);
  std::shared_ptr< iShape > make_shape(Shapes sh);
}

int main()
{
}

void alekseev::scale_pivot(std::weak_ptr< iShape > shape, point_t pivot, double k)
{
  if (k == 1) {
    return;
  }
  if (std::shared_ptr< iShape > locked_shape = shape.lock()) {
    locked_shape->scale(k);
    point_t center = locked_shape->getFrameRect().pos_;
    double x = k * center.x_ - (k - 1) * pivot.x_;
    double y = k * center.y_ - (k - 1) * pivot.y_;
    locked_shape->move(point_t{x, y});
  }
}

std::shared_ptr<alekseev::iShape> alekseev::make_shape(Shapes sh)
{
  if (sh == RECTANGLE) {
    return std::make_shared< Rectangle >(4, 4, point_t{3, 3});
  } else if (sh == CIRCLE) {
    return std::make_shared< Circle >(5, point_t{2, 2});
  } else if (sh == POLYGON) {
    point_t points[]{
      point_t{2, 2},
      point_t{0, 2},
      point_t{0, 0},
      point_t{2, 0}
    };
    return std::make_shared< Polygon >(points, 4);
  } else {
    return nullptr;
  }
}
