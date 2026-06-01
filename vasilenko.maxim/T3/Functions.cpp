#include "Functions.h"
#include <numeric>
#include <algorithm>
#include <cmath>

namespace vasilenko
{
  double crossProduct(const Point& a, const Point& b)
  {
    return static_cast<double>(a.x) * b.y - static_cast<double>(a.y) * b.x;
  }

  double getArea(const Polygon& p)
  {
    if (p.points.size() < 3) {
      return 0.0;
    }
    std::vector<double> products(p.points.size());
    std::transform(p.points.begin(), p.points.end() - 1, p.points.begin() + 1, products.begin(), crossProduct);
    products.back() = crossProduct(p.points.back(), p.points.front());
    double sum = std::accumulate(products.begin(), products.end(), 0.0);
    return std::abs(sum) / 2.0;
  }

  bool isEven(const Polygon& p)
  {
    return p.points.size() % 2 == 0;
  }

  bool isOdd(const Polygon& p)
  {
    return p.points.size() % 2 != 0;
  }

  bool hasVertices(const Polygon& p, size_t n)
  {
    return p.points.size() == n;
  }

  double areaIf(const Polygon& p, std::function<bool(const Polygon&)> pred)
  {
    return pred(p) ? getArea(p) : 0.0;
  }

  bool compareArea(const Polygon& lhs, const Polygon& rhs)
  {
    return getArea(lhs) < getArea(rhs);
  }

  bool compareVertices(const Polygon& lhs, const Polygon& rhs)
  {
    return lhs.points.size() < rhs.points.size();
  }

  bool isTargetDuplicate(const Polygon& lhs, const Polygon& rhs, const Polygon& target)
  {
    return (lhs == target) && (rhs == target);
  }

  bool isOffsetEqual(const Point& p, const Point& t, int dx, int dy)
  {
    return (p.x + dx == t.x) && (p.y + dy == t.y);
  }

  bool isSame(const Polygon& p, const Polygon& target)
  {
    if (p.points.size() != target.points.size()) {
      return false;
    }
    if (p.points.empty()) {
      return true;
    }
    int dx = target.points[0].x - p.points[0].x;
    int dy = target.points[0].y - p.points[0].y;
    return std::equal(p.points.begin(), p.points.end(), target.points.begin(), std::bind(isOffsetEqual, std::placeholders::_1, std::placeholders::_2, dx, dy));
  }
}
