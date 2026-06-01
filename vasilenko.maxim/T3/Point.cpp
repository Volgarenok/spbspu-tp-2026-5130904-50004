#include "Point.h"
#include "Delimiter.h"

namespace vasilenko
{
  bool operator==(const Point& lhs, const Point& rhs)
  {
    return (lhs.x == rhs.x) && (lhs.y == rhs.y);
  }

  std::istream& operator>>(std::istream& in, Point& p)
  {
    std::istream::sentry sentry(in);
    if (!sentry) {
      return in;
    }
    Point temp{0, 0};
    if (in >> DelimiterIO{'('} >> temp.x >> DelimiterIO{';'} >> temp.y >> DelimiterIO{')'}) {
      p = temp;
    }
    return in;
  }
}
