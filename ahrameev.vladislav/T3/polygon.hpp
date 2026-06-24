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

  std::istream& readPoint(std::istream& is, Point& p);
  std::istream& readPolygon(std::istream& is, Polygon& poly);

}

#endif