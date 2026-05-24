#include "complexquad.hpp"

#include <algorithm>
#include <cmath>
#include <stdexcept>

vasilenko::Complexquad::Complexquad(const point_t &a, const point_t &b, const point_t &c, const point_t &d):
  a_(a),
  b_(b),
  c_(c),
  d_(d)
{
  if (!segmentsIntersect(a_, b_, c_, d_) && !segmentsIntersect(b_, c_, d_, a_)) {
    throw std::invalid_argument("Quadrilateral must be self-intersecting");
  }
}

double vasilenko::Complexquad::getArea() const
{
  const point_t center = getCenter();
  if (segmentsIntersect(a_, b_, c_, d_)) {
    return getTriangleArea(a_, d_, center) + getTriangleArea(b_, c_, center);
  } else {
    return getTriangleArea(a_, b_, center) + getTriangleArea(c_, d_, center);
  }
}

vasilenko::rectangle_t vasilenko::Complexquad::getFrameRect() const
{
  const double min_x = std::min({a_.x, b_.x, c_.x, d_.x});
  const double max_x = std::max({a_.x, b_.x, c_.x, d_.x});
  const double min_y = std::min({a_.y, b_.y, c_.y, d_.y});
  const double max_y = std::max({a_.y, b_.y, c_.y, d_.y});

  const double width = max_x - min_x;
  const double height = max_y - min_y;
  const point_t center = {min_x + width / 2.0, min_y + height / 2.0};

  return {width, height, center};
}

void vasilenko::Complexquad::move(const point_t &point)
{
  const point_t center = getCenter();
  move(point.x - center.x, point.y - center.y);
}

void vasilenko::Complexquad::move(double dx, double dy)
{
  a_.x += dx;
  a_.y += dy;
  b_.x += dx;
  b_.y += dy;
  c_.x += dx;
  c_.y += dy;
  d_.x += dx;
  d_.y += dy;
}

void vasilenko::Complexquad::scale(double coefficient)
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

  d_.x = center.x + (d_.x - center.x) * coefficient;
  d_.y = center.y + (d_.y - center.y) * coefficient;
}

bool vasilenko::Complexquad::segmentsIntersect(const point_t &p1, const point_t &p2, const point_t &p3, const point_t &p4) const
{
  const double cp1 = (p2.x - p1.x) * (p3.y - p1.y) - (p2.y - p1.y) * (p3.x - p1.x);
  const double cp2 = (p2.x - p1.x) * (p4.y - p1.y) - (p2.y - p1.y) * (p4.x - p1.x);
  const double cp3 = (p4.x - p3.x) * (p1.y - p3.y) - (p4.y - p3.y) * (p1.x - p3.x);
  const double cp4 = (p4.x - p3.x) * (p2.y - p3.y) - (p4.y - p3.y) * (p2.x - p3.x);
  return (cp1 * cp2 < 0.0) && (cp3 * cp4 < 0.0);
}

vasilenko::point_t vasilenko::Complexquad::getIntersection(const point_t &p1, const point_t &p2, const point_t &p3, const point_t &p4) const
{
  const double a1 = p2.y - p1.y;
  const double b1 = p1.x - p2.x;
  const double c1 = a1 * p1.x + b1 * p1.y;

  const double a2 = p4.y - p3.y;
  const double b2 = p3.x - p4.x;
  const double c2 = a2 * p3.x + b2 * p3.y;

  const double det = a1 * b2 - a2 * b1;
  const double epsilon = 1e-9;

  if (std::abs(det) < epsilon) {
    throw std::logic_error("Lines are parallel");
  }
  return {(b2 * c1 - b1 * c2) / det, (a1 * c2 - a2 * c1) / det};
}

vasilenko::point_t vasilenko::Complexquad::getCenter() const
{
  if (segmentsIntersect(a_, b_, c_, d_)) {
    return getIntersection(a_, b_, c_, d_);
  } else if (segmentsIntersect(b_, c_, d_, a_)) {
    return getIntersection(b_, c_, d_, a_);
  }
  throw std::logic_error("Invalid internal state");
}

double vasilenko::Complexquad::getTriangleArea(const point_t &p1, const point_t &p2, const point_t &p3) const
{
  return std::abs((p2.x - p1.x) * (p3.y - p1.y) - (p3.x - p1.x) * (p2.y - p1.y)) / 2.0;
}
