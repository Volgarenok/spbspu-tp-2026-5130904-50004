#ifndef POLYGON_H
#define POLYGON_H

#include "Point.h"
#include <vector>
#include <iostream>

namespace vasilenko
{
  struct Polygon
  {
    std::vector<Point> points;
  };

  bool operator==(const Polygon& lhs, const Polygon& rhs);
  std::istream& operator>>(std::istream& in, Polygon& p);
}

#endif
