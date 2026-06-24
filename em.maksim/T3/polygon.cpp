#include "polygon.hpp"
#include <cmath>

namespace em {

std::istream& operator>>(std::istream& is, Polygon& poly) {
  size_t count = 0;
  if (!(is >> count)) {
    return is;
  }
  poly.points.clear();
  poly.points.reserve(count);
  for (size_t i = 0; i < count; ++i) {
    Point p;
    if (!(is >> p)) {
      is.setstate(std::ios::failbit);
      return is;
    }
    poly.points.push_back(p);
  }
  return is;
}

std::ostream& operator<<(std::ostream& os, const Polygon& poly) {
  os << poly.points.size();
  for (const auto& p : poly.points) {
    os << " " << p;
  }
  return os;
}

double calculateArea(const Polygon& poly) {
  if (poly.points.size() < 3) {
    return 0.0;
  }
  double area = 0.0;
  const size_t n = poly.points.size();
  for (size_t i = 0; i < n; ++i) {
    const size_t j = (i + 1) % n;
    area += static_cast<double>(poly.points[i].x) * poly.points[j].y;
    area -= static_cast<double>(poly.points[j].x) * poly.points[i].y;
  }
  return std::abs(area) / 2.0;
}

bool hasRightAngle(const Polygon& poly) {
  if (poly.points.size() < 3) {
    return false;
  }
  const size_t n = poly.points.size();
  for (size_t i = 0; i < n; ++i) {
    const size_t prev = (i + n - 1) % n;
    const size_t next = (i + 1) % n;
    const int dx1 = poly.points[i].x - poly.points[prev].x;
    const int dy1 = poly.points[i].y - poly.points[prev].y;
    const int dx2 = poly.points[next].x - poly.points[i].x;
    const int dy2 = poly.points[next].y - poly.points[i].y;
    const int dot = dx1 * dx2 + dy1 * dy2;
    if (dot == 0) {
      return true;
    }
  }
  return false;
}

}  // namespace em
