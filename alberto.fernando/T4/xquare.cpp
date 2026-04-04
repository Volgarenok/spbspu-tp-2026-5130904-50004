#include "xquare.hpp"
#include <stdexcept>

namespace alberto {

Xquare::Xquare(const point_t& center, double halfDiag)
  : center_(center), halfDiag_(halfDiag)
{
  if (halfDiag <= 0.0) {
    throw std::invalid_argument("Xquare: halfDiag must be positive");
  }
}

double Xquare::getArea() const
{
  return 2.0 * halfDiag_ * halfDiag_;
}

rectangle_t Xquare::getFrameRect() const
{
  double diag = 2.0 * halfDiag_;
  return { diag, diag, center_ };
}

void Xquare::move(const point_t& dest)
{
  center_ = dest;
}

void Xquare::move(double dx, double dy)
{
  center_.x += dx;
  center_.y += dy;
}

void Xquare::scale(double factor)
{
  if (factor <= 0.0) {
    throw std::invalid_argument("Xquare::scale: factor must be positive");
  }
  halfDiag_ *= factor;
}

}
