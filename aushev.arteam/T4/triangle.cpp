#include "triangle.hpp"
#include <cmath>
#include <stdexcept>
#include <algorithm>

namespace aushev
{
  Triangle::Triangle(point_t a, point_t b, point_t c):
    a_(a), b_(b), c_(c)
  {
    if (getArea() == 0.0)
    {
      throw std::invalid_argument("Vertices are collinear");
    }
  }

  point_t Triangle::getCentroid() const
  {
    return point_t((a_.x_ + b_.x_ + c_.x_) / 3.0, (a_.y_ + b_.y_ + c_.y_) / 3.0);
  }

  double Triangle::getArea() const
  {
    double val = a_.x_ * (b_.y_ - c_.y_) + b_.x_ * (c_.y_ - a_.y_) + c_.x_ * (a_.y_ - b_.y_);
    return std::abs(val) / 2.0;
  }

  rectangle_t Triangle::getFrameRect() const
  {
    double minX = std::min({a_.x_, b_.x_, c_.x_});
    double maxX = std::max({a_.x_, b_.x_, c_.x_});
    double minY = std::min({a_.y_, b_.y_, c_.y_});
    double maxY = std::max({a_.y_, b_.y_, c_.y_});

    return rectangle_t(maxX - minX, maxY - minY, getCentroid());
  }

  void Triangle::move(const point_t& p)
  {
    point_t center = getCentroid();
    move(p.x_ - center.x_, p.y_ - center.y_);
  }

  void Triangle::move(double dx, double dy)
  {
    a_.x_ += dx; a_.y_ += dy;
    b_.x_ += dx; b_.y_ += dy;
    c_.x_ += dx; c_.y_ += dy;
  }

  void Triangle::scale(double k)
  {
    if (k <= 0.0)
    {
      throw std::invalid_argument("Scale coefficient must be positive");
    }

    point_t center = getCentroid();
    a_ = point_t(center.x_ + (a_.x_ - center.x_) * k, center.y_ + (a_.y_ - center.y_) * k);
    b_ = point_t(center.x_ + (b_.x_ - center.x_) * k, center.y_ + (b_.y_ - center.y_) * k);
    c_ = point_t(center.x_ + (c_.x_ - center.x_) * k, center.y_ + (c_.y_ - center.y_) * k);
  }
}
