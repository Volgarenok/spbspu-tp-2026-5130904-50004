#ifndef AHRAMEEV_POLYGON_HPP
#define AHRAMEEV_POLYGON_HPP

#include <iostream>
#include <vector>

namespace ahrameev
{

  struct Point
  {
    int x;
    int y;
  };

  struct Polygon
  {
    std::vector< Point > points;
  };

  bool lessPoint(const Point& a, const Point& b);
  bool equalPoint(const Point& a, const Point& b);

  bool isPermutation(const Polygon& a, const Polygon& b);

  std::istream& readPoint(std::istream& is, Point& p);
  std::istream& readPolygon(std::istream& is, Polygon& poly);

  bool operator==(const Point& a, const Point& b);

}

#endif