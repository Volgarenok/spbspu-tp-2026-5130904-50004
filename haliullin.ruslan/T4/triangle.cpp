#include "triangle.hpp"
#include <cmath>
#include <stdexcept>
#include <algorithm>

namespace haliullin
{
  Triangle::Triangle(const point_t & a, const point_t & b, const point_t & c) :
    p1(a), p2(b), p3(c),
    pos({(a.x + b.x + c.x) / 3.0, (a.y + b.y + c.y) / 3.0})
  {

    double area = std::abs(
      (p1.x * (p2.y - p3.y) +
       p2.x * (p3.y - p1.y) +
       p3.x * (p1.y - p2.y)) / 2.0
    );

    if (area <= 0.0)
    {
      throw std::invalid_argument("Triangle vertices are collinear");
    }
  }

  double Triangle::getArea() const
  {
    return std::abs(
      (p1.x * (p2.y - p3.y) +
       p2.x * (p3.y - p1.y) +
       p3.x * (p1.y - p2.y)) / 2.0
    );
  }

  rectangle_t Triangle::getFrameRect() const
  {
    double minX = std::min({p1.x, p2.x, p3.x});
    double maxX = std::max({p1.x, p2.x, p3.x});
    double minY = std::min({p1.y, p2.y, p3.y});
    double maxY = std::max({p1.y, p2.y, p3.y});

    double width = maxX - minX;
    double height = maxY - minY;
    point_t center = {minX + width / 2.0, minY + height / 2.0};

    return {width, height, center};
  }

  void Triangle::move(const point_t & pt)
  {
    double dx = pt.x - pos.x;
    double dy = pt.y - pos.y;
    move(dx, dy);
  }

  void Triangle::move(double dx, double dy)
  {
    p1.x += dx;
    p1.y += dy;
    p2.x += dx;
    p2.y += dy;
    p3.x += dx;
    p3.y += dy;
    pos.x += dx;
    pos.y += dy;
  }

  void Triangle::scale(double k)
  {
    if (k <= 0)
    {
      throw std::invalid_argument("Scale coefficient must be positive");
    }

    p1.x = pos.x + (p1.x - pos.x) * k;
    p1.y = pos.y + (p1.y - pos.y) * k;
    p2.x = pos.x + (p2.x - pos.x) * k;
    p2.y = pos.y + (p2.y - pos.y) * k;
    p3.x = pos.x + (p3.x - pos.x) * k;
    p3.y = pos.y + (p3.y - pos.y) * k;
  }
}
