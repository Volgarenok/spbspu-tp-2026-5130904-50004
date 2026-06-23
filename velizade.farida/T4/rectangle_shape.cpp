#include "rectangle_shape.hpp"
#include <stdexcept>

namespace velizade
{

  Rectangle::Rectangle(const point_t& center, double width, double height):
        center_(center),
        width_(width),
        height_(height)
  {
    if (width <= 0 || height <= 0)
    {
      throw std::invalid_argument("Width and height must be positive");
    }
  }

  point_t Rectangle::getCenter() const
  {
    return center_;
  }

  double Rectangle::getArea() const
  {
    return width_ * height_;
  }

  rectangle_t Rectangle::getFrameRect() const
  {
    return {center_, width_, height_};
  }

  void Rectangle::move(const point_t& newPos)
  {
    center_ = newPos;
  }

  void Rectangle::move(double dx, double dy)
  {
    center_.x += dx;
    center_.y += dy;
  }

  void Rectangle::scale(double k)
  {
    if (k <= 0)
    {
      throw std::invalid_argument("Scale factor must be positive");
    }
    width_ *= k;
    height_ *= k;
  }

}
