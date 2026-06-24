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

}
