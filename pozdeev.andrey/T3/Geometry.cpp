#include "Geometry.hpp"
#include "Formatters.hpp"
#include <iterator>
#include <algorithm>

namespace pozdeev
{
  std::istream& operator>>(std::istream& in, Point& dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    in >> DelimiterIO{'('} >> dest.x >> DelimiterIO{';'} >> dest.y >> DelimiterIO{')'};
    return in;
  }

  std::istream& operator>>(std::istream& in, Polygon& dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    size_t size = 0;
    if (!(in >> size))
    {
      return in;
    }
    if (size < 3)
    {
      in.setstate(std::ios::failbit);
      return in;
    }
    Polygon temp;
    std::copy_n(std::istream_iterator< Point >(in), size, std::back_inserter(temp.points));
    if (in)
    {
      dest = temp;
    }
    return in;
  }

  bool operator==(const Point& lhs, const Point& rhs)
  {
    return lhs.x == rhs.x && lhs.y == rhs.y;
  }
}
