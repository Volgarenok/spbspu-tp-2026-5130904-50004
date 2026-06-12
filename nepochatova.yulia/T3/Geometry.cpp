#include "Geometry.h"
#include "IOGuard.h"
#include <limits>
#include <algorithm>

namespace nepochatova {
  struct SemiDelim {
    char c;
  };

  std::istream& operator>>(std::istream& in, SemiDelim&& d) {
    std::istream::sentry s(in);
    if (!s) return in;
    char ch;
    if (!(in >> ch) || ch != d.c)
      in.setstate(std::ios_base::failbit);
    return in;
  }

  bool Point::operator==(const Point& other) const {
    return x == other.x && y == other.y;
  }

  bool Polygon::operator==(const Polygon& other) const {
    if (points.size() != other.points.size()) return false;
    return std::equal(points.begin(), points.end(), other.points.begin());
  }

  double Polygon::area() const {
    if (points.size() < 3) {
      return 0.0;
    }
    double s = 0.0;
    for (size_t i = 0; i < points.size(); ++i) {
      size_t j = (i + 1) % points.size();
      s += static_cast<double>(points[i].x) * points[j].y;
      s -= static_cast<double>(points[j].x) * points[i].y;
    }
    return std::abs(s) / 2.0;
  }

  std::istream& operator>>(std::istream& in, PointIO&& dest) {
    std::istream::sentry s(in);
    if (!s) return in;

    char dummy = 0;

    in >> DelimiterIO{'(', dummy}
    >> dest.ref.x
    >> SemiDelim{';'}
    >> dest.ref.y
    >> DelimiterIO{')', dummy};

    return in;
  }

  std::istream& operator>>(std::istream& in, Polygon& poly) {
    std::istream::sentry s(in);
    if (!s) return in;

    size_t n;
    if (!(in >> n)) return in;

    poly.points.clear();
    poly.points.reserve(n);

    for (size_t i = 0; i < n; ++i) {
      Point p;
      if (!(in >> PointIO{p})) {
        in.setstate(std::ios_base::failbit);
        return in;
      }
      poly.points.push_back(p);
    }
    return in;
  }
}