#include "concave.hpp"

#include <stdexcept>

namespace ali
{
  double triangleArea(
    const point_t & a,
    const point_t & b,
    const point_t & c)
  {
    double area =
      ((a.x * (b.y - c.y)) +
      (b.x * (c.y - a.y)) +
      (c.x * (a.y - b.y))) / 2.0;

    return (area < 0 ? -area : area);
  }

  Concave::Concave(
    const point_t & a,
    const point_t & b,
    const point_t & c,
    const point_t & d):
    a_(a),
    b_(b),
    c_(c),
    d_(d)
  {}

  double Concave::getArea() const
  {
    return triangleArea(a_, b_, c_) +
           triangleArea(a_, c_, d_);
  }

  rectangle_t Concave::getFrameRect() const
  {
    point_t points[4] = { a_, b_, c_, d_ };

    double minX = points[0].x;
    double maxX = points[0].x;
    double minY = points[0].y;
    double maxY = points[0].y;

    for (int i = 0; i < 4; ++i)
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

  void Concave::move(const point_t & pos)
  {
    rectangle_t rect = getFrameRect();

    double dx = pos.x - rect.pos.x;
    double dy = pos.y - rect.pos.y;

    move(dx, dy);
  }

  void Concave::move(double dx, double dy)
  {
    a_.x += dx;
    a_.y += dy;

    b_.x += dx;
    b_.y += dy;

    c_.x += dx;
    c_.y += dy;

    d_.x += dx;
    d_.y += dy;
  }

  void Concave::scale(double k)
  {
    if (k <= 0)
    {
      throw std::invalid_argument("invalid scale");
    }

    rectangle_t rect = getFrameRect();
    point_t center = rect.pos;

    point_t * points[4] = { &a_, &b_, &c_, &d_ };

    for (int i = 0; i < 4; ++i)
    {
      (*points[i]).x =
        center.x + ((*points[i]).x - center.x) * k;

      (*points[i]).y =
        center.y + ((*points[i]).y - center.y) * k;
    }
  }
}

