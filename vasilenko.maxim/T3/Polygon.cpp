#include "Polygon.h"
#include <iterator>
#include <algorithm>

namespace vasilenko
{
  bool operator==(const Polygon& lhs, const Polygon& rhs)
  {
    if (lhs.points.size() != rhs.points.size()) {
      return false;
    }
    return std::equal(lhs.points.begin(), lhs.points.end(), rhs.points.begin());
  }

  std::istream& operator>>(std::istream& in, Polygon& p)
  {
    std::istream::sentry sentry(in);
    if (!sentry) {
      return in;
    }
    size_t count = 0;
    if (!(in >> count) || count < 3) {
      in.setstate(std::ios::failbit);
      return in;
    }
    std::vector<Point> pts;
    pts.reserve(count);
    std::copy_n(std::istream_iterator<Point>(in), count, std::back_inserter(pts));

    if (in) {
      p.points = pts;
    }
    return in;
  }
}
