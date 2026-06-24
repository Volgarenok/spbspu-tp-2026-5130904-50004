#ifndef EM_POINT_HPP
#define EM_POINT_HPP

#include <iosfwd>

namespace em
{
  struct Point
  {
    int x;
    int y;
  };

  std::istream & operator>>(std::istream & is, Point & p);
  std::ostream & operator<<(std::ostream & os, const Point & p);
}

#endif
