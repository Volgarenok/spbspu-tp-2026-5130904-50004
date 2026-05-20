#include "geometry.hpp"

#include <cmath>

namespace ali
{
  std::istream & operator>>(std::istream & in, Point & point)
  {
    char c = '\0';

    in >> c;

    if (!in || c != '(')
    {
      in.setstate(std::ios::failbit);
      return in;
    }

    in >> point.x >> c;

    if (c != ';')
    {
      in.setstate(std::ios::failbit);
      return in;
    }

    in >> point.y >> c;

    if (c != ')')
    {
      in.setstate(std::ios::failbit);
      return in;
    }

    return in;
  }

  std::istream & operator>>(std::istream & in, Polygon & polygon)
  {
    std::size_t count = 0;
    in >> count;

    if (!in || count < 3)
    {
      in.setstate(std::ios::failbit);
      return in;
    }

    Polygon temp;

    for (std::size_t i = 0; i < count; ++i)
    {
      Point point{};
      in >> point;

      if (!in)
      {
        return in;
      }

      temp.points.push_back(point);
    }

    polygon = temp;

    return in;
  }

  std::ostream & operator<<(std::ostream & out, const Point & point)
  {
    out << '(' << point.x << ';' << point.y << ')';
    return out;
  }

  std::ostream & operator<<(std::ostream & out, const Polygon & polygon)
  {
    out << polygon.points.size();

    for (const auto & point: polygon.points)
    {
      out << ' ' << point;
    }

    return out;
  }

  bool operator==(const Point & a, const Point & b)
  {
    return a.x == b.x && a.y == b.y;
  }

  bool operator==(const Polygon & a, const Polygon & b)
  {
    return a.points == b.points;
  }

  double getArea(const Polygon & polygon)
  {
    double area = 0.0;

    for (std::size_t i = 0; i < polygon.points.size(); ++i)
    {
      std::size_t j = (i + 1) % polygon.points.size();

      area += polygon.points[i].x * polygon.points[j].y;
      area -= polygon.points[j].x * polygon.points[i].y;
    }

    area = std::abs(area) / 2.0;

    return area;
  }

  bool isRectangle(const Polygon & polygon)
  {
    return polygon.points.size() == 4;
  }
}
