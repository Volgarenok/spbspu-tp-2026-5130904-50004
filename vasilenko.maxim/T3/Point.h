#ifndef POINT_H
#define POINT_H

#include <iostream>

namespace vasilenko
{
  struct Point
  {
    int x, y;
  };

  bool operator==(const Point& lhs, const Point& rhs);
  std::istream& operator>>(std::istream& in, Point& p);
}

#endif
