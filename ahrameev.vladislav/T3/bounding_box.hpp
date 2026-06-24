#ifndef AHRAMEEV_BOUNDING_BOX_HPP
#define AHRAMEEV_BOUNDING_BOX_HPP

#include "polygon.hpp"

#include <vector>

namespace ahrameev
{

  struct BoundingBox
  {
    int minX;
    int maxX;
    int minY;
    int maxY;
    bool isValid;
  };

  bool lessByX(const Point& a, const Point& b);
  bool lessByY(const Point& a, const Point& b);

  bool isPointInsideBox(const BoundingBox& box, const Point& p);
  bool isPolygonInsideBox(const BoundingBox& box, const Polygon& poly);

  BoundingBox computeBoundingBoxOfPolygon(const Polygon& poly);
  BoundingBox computeGlobalBoundingBox(const std::vector< Polygon >& polygons);

}

#endif