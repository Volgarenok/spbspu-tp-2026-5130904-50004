#include "diamond.hpp"
#include <cmath>
#include <stdexcept>

namespace haliullin
{
  Diamond::Diamond(double g, double v, const point_t & p) :
    gor_d(g), vert_d(v), pos(p)
  {
    if (gor_d <= 0.0 || vert_d <= 0.0)
    {
      throw std::invalid_argument("Diagonals must be positive");
    }
  }

  double Diamond::getArea() const
  {
    return (gor_d * vert_d) / 2.0;
  }

  rectangle_t Diamond::getFrameRect() const
  {
    return {gor_d, vert_d, pos};
  }

  void Diamond::move(const point_t & pt)
  {
    pos = pt;
  }

  void Diamond::move(double dx, double dy)
  {
    pos.x += dx;
    pos.y += dy;
  }

  void Diamond::scale(double k)
  {
    if (k <= 0.0)
    {
      throw std::invalid_argument("Scale coefficient must be positive");
    }
    gor_d *= k;
    vert_d *= k;
  }
}
