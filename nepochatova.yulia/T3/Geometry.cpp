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