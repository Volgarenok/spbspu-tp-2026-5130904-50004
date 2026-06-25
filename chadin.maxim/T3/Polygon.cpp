#include "Polygon.h"
#include <algorithm>
#include <iterator>

namespace chadin {
  namespace detail {

    struct read_point
    {
      std::istream& in;
      Point operator()() const
      {
        Point p;
        in >> p;
        return p;
      }
    };

  }

  bool operator==(const Point& lhs, const Point& rhs)
  {
    return lhs.x == rhs.x && lhs.y == rhs.y;
  }

  std::istream& operator>>(std::istream& in, Point& point)
  {
    std::istream::sentry sentry(in);
    if (!sentry) {
      return in;
    }
    char c1 = '\0';
    char c2 = '\0';
    char c3 = '\0';
    int x = 0;
    int y = 0;
    if (in >> c1 >> x >> c2 >> y >> c3) {
      if (c1 == '(' && c2 == ';' && c3 == ')') {
        point.x = x;
        point.y = y;
      } else {
        in.setstate(std::ios::failbit);
      }
    }
    return in;
  }
