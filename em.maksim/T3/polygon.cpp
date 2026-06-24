#include "polygon.hpp"

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

}
