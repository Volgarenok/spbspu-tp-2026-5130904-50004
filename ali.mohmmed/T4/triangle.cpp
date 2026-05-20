#include "triangle.hpp"

#include <stdexcept>

namespace ali
{
  double getTriangleArea(const point_t & a, const point_t & b, const point_t & c)
  {
    return ((a.x * (b.y - c.y)) +
            (b.x * (c.y - a.y)) +
            (c.x * (a.y - b.y))) / 2.0;
  }

  Triangle::Triangle(const point_t & a, const point_t & b, const point_t & c):
    a_(a),
    b_(b),
    c_(c)
  {
    if (getArea() == 0.0)
    {
      throw std::invalid_argument("invalid triangle");
    }
  }

  double Triangle::getArea() const
  {
    double area = getTriangleArea(a_, b_, c_);

    return (area < 0 ? -area : area);
  }

  rectangle_t Triangle::getFrameRect() const
  {
    double minX = a_.x;
    double maxX = a_.x;
    double minY = a_.y;
    double maxY = a_.y;

    point_t points[3] = { a_, b_, c_ };

    for (int i = 0; i < 3; ++i)
    {
      if (points[i].x < minX)
      {
        minX = points[i].x;
      }

      if (points[i].x > maxX)
      {
        maxX = points[i].x;
      }

      if (points[i].y < minY)
      {
        minY = points[i].y;
      }

      if (points[i].y > maxY)
      {
        maxY = points[i].y;
      }
    }

    return {
      maxX - minX,
      maxY - minY,
      { (minX + maxX) / 2.0, (minY + maxY) / 2.0 }
    };
  }

  void Triangle::move(const point_t & pos)
  {
    rectangle_t rect = getFrameRect();

    double dx = pos.x - rect.pos.x;
    double dy = pos.y - rect.pos.y;

    move(dx, dy);
  }

  void Triangle::move(double dx, double dy)
  {
    a_.x += dx;
    a_.y += dy;

    b_.x += dx;
    b_.y += dy;

    c_.x += dx;
    c_.y += dy;
  }

  void Triangle::scale(double k)
  {
    if (k <= 0)
    {
      throw std::invalid_argument("invalid scale");
    }

    rectangle_t rect = getFrameRect();
    point_t center = rect.pos;

    a_.x = center.x + (a_.x - center.x) * k;
    a_.y = center.y + (a_.y - center.y) * k;

    b_.x = center.x + (b_.x - center.x) * k;
    b_.y = center.y + (b_.y - center.y) * k;

    c_.x = center.x + (c_.x - center.x) * k;
    c_.y = center.y + (c_.y - center.y) * k;
  }
}
