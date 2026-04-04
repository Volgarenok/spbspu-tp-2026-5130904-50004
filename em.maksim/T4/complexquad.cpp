#include "complexquad.hpp"

#include <cmath>

namespace em {

point_t Complexquad::findIntersection(point_t p1, point_t p2, point_t p3, point_t p4)
{
  double x1 = p1.x_;
  double y1 = p1.y_;
  double x2 = p2.x_;
  double y2 = p2.y_;
  double x3 = p3.x_;
  double y3 = p3.y_;
  double x4 = p4.x_;
  double y4 = p4.y_;

  double den = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4);
  if (std::abs(den) < 1e-9) {
    return {(x1 + x2 + x3 + x4) / 4.0, (y1 + y2 + y3 + y4) / 4.0};
  }

  double x = ((x1 * y2 - y1 * x2) * (x3 - x4) - (x1 - x2) * (x3 * y4 - y3 * x4)) / den;
  double y = ((x1 * y2 - y1 * x2) * (y3 - y4) - (y1 - y2) * (x3 * y4 - y3 * x4)) / den;

  return {x, y};
}

}

void Complexquad::recalcCenter()
{
  center_ = findIntersection(vertices_[0], vertices_[2], vertices_[1], vertices_[3]);
}

Complexquad::Complexquad(std::array<point_t, 4> vertices)
  : vertices_{vertices}
{
  recalcCenter();
}

double Complexquad::getArea() const
{
  double sum = 0.0;
  for (size_t i = 0; i < 4; ++i) {
    size_t j = (i + 1) % 4;
    sum += vertices_[i].x_ * vertices_[j].y_;
    sum -= vertices_[j].x_ * vertices_[i].y_;
  }

  return std::abs(sum) / 2.0;
}
