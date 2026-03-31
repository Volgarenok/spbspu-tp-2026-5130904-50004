#include "circle.hpp"
#include <cmath>

double zinoviev::Circle::getArea() const
{
  const double PI = std::acos(-1.0);

  return PI * radius_ * radius_;
}

zinoviev::rectangle_t zinoviev::Circle::getFrameRect() const
{
  return rectangle_t(center_, 2 * radius_, 2 * radius_);
}

void zinoviev::Circle::move(const point_t& newPos)
{
  center_ = newPos;
}

void zinoviev::Circle::move(double dx, double dy)
{
  center_.x += dx;
  center_.y += dy;
}

void zinoviev::Circle::scale(double k)
{
  if (k <= 0.0)
    throw std::logic_error("Coefficient must be positive");

  radius_ *= k;
}
