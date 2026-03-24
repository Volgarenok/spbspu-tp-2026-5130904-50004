#include "rectangle.hpp"
#include <stdexcept>

namespace haliullin
{
  Rectangle::Rectangle(double w, double h, const point_t & p) :
    width(w), height(h), pos(p)
  {
    if (width <= 0.0 || height <= 0.0)
    {
      throw std::invalid_argument("Sizes must be positive");
    }
  }

  double Rectangle::getArea() const
  {
    return width * height;
  }

  rectangle_t Rectangle::getFrameRect() const
  {
    return {width, height, pos};
  }

  void Rectangle::move(const point_t & pt)
  {
    pos = pt;
  }

  void Rectangle::move(double dx, double dy)
  {
    pos.x += dx;
    pos.y += dy;
  }

  void Rectangle::scale(double k)
  {
    if (k <= 0.0)
    {
      throw std::invalid_argument("Scale coefficient must be positive");
    }
    width *= k;
    height *= k;
  }
}
