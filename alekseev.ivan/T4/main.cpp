#include "Shape.h"
#include <memory>
#include <iostream>

namespace alekseev {
  void scale_pivot(std::weak_ptr< iShape > shape, point_t pivot, double k);
}

int main()
{
  std::shared_ptr< alekseev::Circle > c = std::make_shared< alekseev::Circle >(1,
      alekseev::point_t{2, 2});
  alekseev::scale_pivot(c, alekseev::point_t{3, 4}, 3);
  alekseev::point_t p = c->getFrameRect().pos_;
  std::cout << c->getArea() << " " << p.x_ << " " << p.y_ << "\n";
}

void alekseev::scale_pivot(std::weak_ptr< iShape > shape, point_t pivot, double k)
{
  if (k == 1) {
    return;
  }
  if (std::shared_ptr< iShape > locked_shape = shape.lock()) {
    locked_shape->scale(k);
    point_t center = locked_shape->getFrameRect().pos_;
    double l = k ? k - 1 : -1;
    double x = (1 + l) * center.x_ - l * pivot.x_;
    double y = (1 + l) * center.y_ - l * pivot.y_;
    locked_shape->move(point_t{x, y});
  }
}
