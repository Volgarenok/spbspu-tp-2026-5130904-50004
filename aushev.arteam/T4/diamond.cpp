#include "diamond.hpp"
#include <stdexcept>

namespace aushev
{
  Diamond::Diamond(double d1, double d2, point_t pos):
    d1_(d1), d2_(d2), pos_(pos)
  {
    if (d1_ <= 0.0 || d2_ <= 0.0)
    {
      throw std::invalid_argument("Diagonals must be positive");
    }
  }

  double Diamond::getArea() const
  {
    return (d1_ * d2_) / 2.0;
  }

  rectangle_t Diamond::getFrameRect() const
  {
    return rectangle_t(d1_, d2_, pos_);
  }

  void Diamond::move(const point_t& p)
  {
    pos_ = p;
  }

  void Diamond::move(double dx, double dy)
  {
    pos_.x_ += dx;
    pos_.y_ += dy;
  }

  void Diamond::scale(double k)
  {
    if (k <= 0.0)
    {
      throw std::invalid_argument("Scale coefficient must be positive");
    }
    d1_ *= k;
    d2_ *= k;
  }
}
