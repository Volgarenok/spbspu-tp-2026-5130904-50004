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

  bool compareArea(const Polygon& a, const Polygon& b);
  bool compareVertexes(const Polygon& a, const Polygon& b);

  bool comparePointX(const Point& a, const Point& b);
  bool comparePointY(const Point& a, const Point& b);
  bool compareMinX(const Polygon& a, const Polygon& b);
  bool compareMaxX(const Polygon& a, const Polygon& b);
  bool compareMinY(const Polygon& a, const Polygon& b);
  bool compareMaxY(const Polygon& a, const Polygon& b);

  int getMinX(const Polygon& p);
  int getMaxX(const Polygon& p);
  int getMinY(const Polygon& p);
  int getMaxY(const Polygon& p);

  bool isSameOffset(const Point& p1, const Point& p2, const Point& offset);
  bool isSame(const Polygon& p1, const Polygon& p2);
}

#endif
