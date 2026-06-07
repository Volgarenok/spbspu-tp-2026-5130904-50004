#include "Geometry.hpp"
#include "Formatters.hpp"
#include <iterator>
#include <algorithm>
#include <numeric>
#include <cmath>

namespace pozdeev
{
  std::istream& operator>>(std::istream& in, Point& dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    in >> DelimiterIO{'('} >> dest.x >> DelimiterIO{';'} >> dest.y >> DelimiterIO{')'};
    return in;
  }

  std::istream& operator>>(std::istream& in, Polygon& dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    size_t size = 0;
    if (!(in >> size))
    {
      return in;
    }
    if (size < 3)
    {
      in.setstate(std::ios::failbit);
      return in;
    }
    Polygon temp;
    std::copy_n(std::istream_iterator< Point >(in), size, std::back_inserter(temp.points));
    if (in)
    {
      dest = temp;
    }
    return in;
  }

  bool operator==(const Point& lhs, const Point& rhs)
  {
    return lhs.x == rhs.x && lhs.y == rhs.y;
  }

  double crossProduct(const Point& a, const Point& b)
  {
    return static_cast< double >(a.x) * b.y - static_cast< double >(a.y) * b.x;
  }

  double getArea(const Polygon& p)
  {
    std::vector< double > products(p.points.size());
    std::transform(p.points.begin(), p.points.end() - 1, p.points.begin() + 1, products.begin(), crossProduct);
    products.back() = crossProduct(p.points.back(), p.points.front());
    double sum = std::accumulate(products.begin(), products.end(), 0.0);
    return std::abs(sum) / 2.0;
  }

  double getAreaIfEven(const Polygon& p)
  {
    return isEven(p) ? getArea(p) : 0.0;
  }

  double getAreaIfOdd(const Polygon& p)
  {
    return isOdd(p) ? getArea(p) : 0.0;
  }

  double getAreaIfNum(const Polygon& p, size_t vertexes)
  {
    return hasVertexes(p, vertexes) ? getArea(p) : 0.0;
  }

  bool isEven(const Polygon& p)
  {
    return p.points.size() % 2 == 0;
  }

  bool isOdd(const Polygon& p)
  {
    return p.points.size() % 2 != 0;
  }

  bool hasVertexes(const Polygon& p, size_t vertexes)
  {
    return p.points.size() == vertexes;
  }

  bool compareArea(const Polygon& a, const Polygon& b)
  {
    return getArea(a) < getArea(b);
  }

  bool compareVertexes(const Polygon& a, const Polygon& b)
  {
    return a.points.size() < b.points.size();
  }

  bool comparePointX(const Point& a, const Point& b)
  {
    return a.x < b.x;
  }

  bool comparePointY(const Point& a, const Point& b)
  {
    return a.y < b.y;
  }

  int getMinX(const Polygon& p)
  {
    return std::min_element(p.points.begin(), p.points.end(), comparePointX)->x;
  }

  int getMaxX(const Polygon& p)
  {
    return std::max_element(p.points.begin(), p.points.end(), comparePointX)->x;
  }

  int getMinY(const Polygon& p)
  {
    return std::min_element(p.points.begin(), p.points.end(), comparePointY)->y;
  }

  int getMaxY(const Polygon& p)
  {
    return std::max_element(p.points.begin(), p.points.end(), comparePointY)->y;
  }

  bool compareMinX(const Polygon& a, const Polygon& b)
  {
    return getMinX(a) < getMinX(b);
  }

  bool compareMaxX(const Polygon& a, const Polygon& b)
  {
    return getMaxX(a) < getMaxX(b);
  }

  bool compareMinY(const Polygon& a, const Polygon& b)
  {
    return getMinY(a) < getMinY(b);
  }

  bool compareMaxY(const Polygon& a, const Polygon& b)
  {
    return getMaxY(a) < getMaxY(b);
  }
}
