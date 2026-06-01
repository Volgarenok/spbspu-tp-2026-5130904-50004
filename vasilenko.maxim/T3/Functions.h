#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "Polygon.h"
#include <functional>

namespace vasilenko
{
  double crossProduct(const Point& a, const Point& b);
  double getArea(const Polygon& p);

  bool isEven(const Polygon& p);
  bool isOdd(const Polygon& p);
  bool hasVertices(const Polygon& p, size_t n);

  double areaIf(const Polygon& p, std::function<bool(const Polygon&)> pred);

  bool compareArea(const Polygon& lhs, const Polygon& rhs);
  bool compareVertices(const Polygon& lhs, const Polygon& rhs);

  bool isTargetDuplicate(const Polygon& lhs, const Polygon& rhs, const Polygon& target);
  bool isOffsetEqual(const Point& p, const Point& t, int dx, int dy);
  bool isSame(const Polygon& p, const Polygon& target);
}

#endif
