#include "bounding_box.hpp"

#include <algorithm>
#include <functional>

namespace ahrameev
{

  bool lessByX(const Point& a, const Point& b)
  {
    return a.x < b.x;
  }

  bool lessByY(const Point& a, const Point& b)
  {
    return a.y < b.y;
  }

  bool isPointInsideBox(const BoundingBox& box, const Point& p)
  {
    return (p.x >= box.minX) && (p.x <= box.maxX)
      && (p.y >= box.minY) && (p.y <= box.maxY);
  }

  bool isPolygonInsideBox(const BoundingBox& box, const Polygon& poly)
  {
    return std::all_of(
      poly.points.cbegin(),
      poly.points.cend(),
      std::bind(isPointInsideBox, box, std::placeholders::_1)
    );
  }

  namespace
  {

    BoundingBox makeEmptyBoundingBox()
    {
      BoundingBox box{};
      box.minX = 0;
      box.maxX = 0;
      box.minY = 0;
      box.maxY = 0;
      box.isValid = false;
      return box;
    }

    int findMinX(const std::vector< Point >& points)
    {
      auto it = std::min_element(points.cbegin(), points.cend(), lessByX);
      return it->x;
    }

    int findMaxX(const std::vector< Point >& points)
    {
      auto it = std::max_element(points.cbegin(), points.cend(), lessByX);
      return it->x;
    }

    int findMinY(const std::vector< Point >& points)
    {
      auto it = std::min_element(points.cbegin(), points.cend(), lessByY);
      return it->y;
    }

    int findMaxY(const std::vector< Point >& points)
    {
      auto it = std::max_element(points.cbegin(), points.cend(), lessByY);
      return it->y;
    }

    BoundingBox buildBoxFromPoints(const std::vector< Point >& points)
    {
      BoundingBox box{};
      box.minX = findMinX(points);
      box.maxX = findMaxX(points);
      box.minY = findMinY(points);
      box.maxY = findMaxY(points);
      box.isValid = true;
      return box;
    }

  }

  BoundingBox computeBoundingBoxOfPolygon(const Polygon& poly)
  {
    if (poly.points.empty())
    {
      return makeEmptyBoundingBox();
    }
    return buildBoxFromPoints(poly.points);
  }

  namespace
  {

    struct PolygonBounds
    {
      int minX;
      int maxX;
      int minY;
      int maxY;
    };

    PolygonBounds extractBounds(const Polygon& poly)
    {
      BoundingBox box = computeBoundingBoxOfPolygon(poly);
      PolygonBounds bounds{};
      bounds.minX = box.minX;
      bounds.maxX = box.maxX;
      bounds.minY = box.minY;
      bounds.maxY = box.maxY;
      return bounds;
    }

    bool lessByPolygonMinX(const PolygonBounds& a, const PolygonBounds& b)
    {
      return a.minX < b.minX;
    }

    bool lessByPolygonMaxX(const PolygonBounds& a, const PolygonBounds& b)
    {
      return a.maxX < b.maxX;
    }

    bool lessByPolygonMinY(const PolygonBounds& a, const PolygonBounds& b)
    {
      return a.minY < b.minY;
    }

    bool lessByPolygonMaxY(const PolygonBounds& a, const PolygonBounds& b)
    {
      return a.maxY < b.maxY;
    }

    std::vector< PolygonBounds > collectAllBounds(const std::vector< Polygon >& polygons)
    {
      std::vector< PolygonBounds > bounds;
      bounds.reserve(polygons.size());
      std::transform(
        polygons.cbegin(),
        polygons.cend(),
        std::back_inserter(bounds),
        extractBounds
      );
      return bounds;
    }

    int findGlobalMinX(const std::vector< PolygonBounds >& bounds)
    {
      auto it = std::min_element(bounds.cbegin(), bounds.cend(), lessByPolygonMinX);
      return it->minX;
    }

    int findGlobalMaxX(const std::vector< PolygonBounds >& bounds)
    {
      auto it = std::max_element(bounds.cbegin(), bounds.cend(), lessByPolygonMaxX);
      return it->maxX;
    }

    int findGlobalMinY(const std::vector< PolygonBounds >& bounds)
    {
      auto it = std::min_element(bounds.cbegin(), bounds.cend(), lessByPolygonMinY);
      return it->minY;
    }

    int findGlobalMaxY(const std::vector< PolygonBounds >& bounds)
    {
      auto it = std::max_element(bounds.cbegin(), bounds.cend(), lessByPolygonMaxY);
      return it->maxY;
    }

    BoundingBox buildGlobalBox(const std::vector< PolygonBounds >& bounds)
    {
      BoundingBox box{};
      box.minX = findGlobalMinX(bounds);
      box.maxX = findGlobalMaxX(bounds);
      box.minY = findGlobalMinY(bounds);
      box.maxY = findGlobalMaxY(bounds);
      box.isValid = true;
      return box;
    }

  }

  BoundingBox computeGlobalBoundingBox(const std::vector< Polygon >& polygons)
  {
    if (polygons.empty())
    {
      return makeEmptyBoundingBox();
    }
    std::vector< PolygonBounds > bounds = collectAllBounds(polygons);
    if (bounds.empty())
    {
      return makeEmptyBoundingBox();
    }
    return buildGlobalBox(bounds);
  }

}