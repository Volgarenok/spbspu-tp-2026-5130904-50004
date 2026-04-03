#include "triangle.hpp"

#include <algorithm>
#include <cmath>
#include <stdexcept>

vasilenko::Triangle::Triangle(const point_t &a, const point_t &b, const point_t &c):
  a_(a),
  b_(b),
  c_(c)
{
}

double vasilenko::Triangle::getArea() const
{
  const double area = std::abs((b_.x - a_.x) * (c_.y - a_.y) - (c_.x - a_.x) * (b_.y - a_.y)) / 2.0;
  return area;
}

vasilenko::rectangle_t vasilenko::Triangle::getFrameRect() const
{
  const double min_x = std::min({a_.x, b_.x, c_.x});
  const double max_x = std::max({a_.x, b_.x, c_.x});
  const double min_y = std::min({a_.y, b_.y, c_.y});
  const double max_y = std::max({a_.y, b_.y, c_.y});

  const double width = max_x - min_x;
  const double height = max_y - min_y;
  const point_t center = {min_x + width / 2.0, min_y + height / 2.0};

  return {width, height, center};
}

void vasilenko::Triangle::move(const point_t &point)
{
  const point_t center = getCenter();
  move(point.x - center.x, point.y - center.y);
}

void vasilenko::Triangle::move(double dx, double dy)
{
  a_.x += dx;
  a_.y += dy;
  b_.x += dx;
  b_.y += dy;
  c_.x += dx;
  c_.y += dy;
}

void vasilenko::Triangle::scale(double coefficient)
{
  if (coefficient <= 0.0) {
    throw std::invalid_argument("Scale coefficient must be positive");
  }
  const point_t center = getCenter();

  a_.x = center.x + (a_.x - center.x) * coefficient;
  a_.y = center.y + (a_.y - center.y) * coefficient;

  b_.x = center.x + (b_.x - center.x) * coefficient;
  b_.y = center.y + (b_.y - center.y) * coefficient;

  c_.x = center.x + (c_.x - center.x) * coefficient;
  c_.y = center.y + (c_.y - center.y) * coefficient;
}

vasilenko::point_t vasilenko::Triangle::getCenter() const
{
  return {(a_.x + b_.x + c_.x) / 3.0, (a_.y + b_.y + c_.y) / 3.0};
}
