#include "Shape.h"
#include <memory>
#include <iostream>

namespace alekseev {
  void scale_pivot(std::weak_ptr< iShape > shape, point_t pivot, double k);
}

int main()
{
  size_t N = 4;
  alekseev::point_t points[]{
    alekseev::point_t{1 + 1, 1 + 1},
    alekseev::point_t{-1 + 1, 3},
    alekseev::point_t{-1 + 1, -1 + 1},
    alekseev::point_t{1 + 1, -1 + 1}
  };

  std::shared_ptr< alekseev::Polygon > c = std::make_shared< alekseev::Polygon >(points, N);

  alekseev::scale_pivot(c, alekseev::point_t{0, 0}, 3);

  alekseev::point_t * p = c->get_points();
  for (size_t i = 0; i < N; ++i) {
    std::cout << "\t" << p[i].x_ << ", " << p[i].y_ << "\n";
  }
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
