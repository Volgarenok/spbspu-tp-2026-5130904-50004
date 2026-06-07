#ifndef GEOMETRY_HPP
#define GEOMETRY_HPP

#include <iostream>
#include <vector>

namespace pozdeev
{
  struct Point
  {
    int x, y;
  };

  struct Polygon
  {
    std::vector< Point > points;
  };

  std::istream& operator>>(std::istream& in, Point& dest);
  std::istream& operator>>(std::istream& in, Polygon& dest);
  bool operator==(const Point& lhs, const Point& rhs);

  double crossProduct(const Point& a, const Point& b);
  double getArea(const Polygon& p);
  double getAreaIfEven(const Polygon& p);
  double getAreaIfOdd(const Polygon& p);
  double getAreaIfNum(const Polygon& p, size_t vertexes);

  bool isEven(const Polygon& p);
  bool isOdd(const Polygon& p);
  bool hasVertexes(const Polygon& p, size_t vertexes);
}
