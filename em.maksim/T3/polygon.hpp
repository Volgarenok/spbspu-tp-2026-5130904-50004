#ifndef EM_POLYGON_HPP
#define EM_POLYGON_HPP

#include "point.hpp"
#include <vector>
#include <iosfwd>

namespace em
{
  struct Polygon
  {
    std::vector< Point > points;
  };

  std::istream & operator>>(std::istream & is, Polygon & poly);
  std::ostream & operator<<(std::ostream & os, const Polygon & poly);

  double calculateArea(const Polygon & poly);
  bool hasRightAngle(const Polygon & poly);

  struct BoundingBox
  {
    int minX;
    int minY;
    int maxX;
    int maxY;
  };

  BoundingBox getBoundingBox(const std::vector< Polygon > & shapes);
  bool isInsideFrame(const Polygon & poly, const BoundingBox & box);
}

#endif
