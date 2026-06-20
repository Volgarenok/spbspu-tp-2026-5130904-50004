#include "xquare.hpp"
#include <stdexcept>
#include <cmath>

namespace velizade
{

  Xsquare::Xsquare(const point_t& center, double halfDiag):
        center_(center),
        halfDiag_(halfDiag)
  {
    if (halfDiag <= 0)
    {
      throw std::invalid_argument("Half diagonal must be positive");
    }
  }

  point_t Xsquare::getCenter() const
  {
    return center_;
  }

  double Xsquare::getArea() const
  {
    return 2.0 * halfDiag_ * halfDiag_;
  }

  rectangle_t Xsquare::getFrameRect() const
  {
    return {center_, 2 * halfDiag_, 2 * halfDiag_};
  }

  void Xsquare::move(const point_t& newPos)
  {
    center_ = newPos;
  }

  void Xsquare::move(double dx, double dy)
  {
    center_.x += dx;
    center_.y += dy;
  }

  void Xsquare::scale(double k)
  {
    if (k <= 0)
    {
      throw std::invalid_argument("Scale factor must be positive");
    }
    halfDiag_ *= k;
  }

}
