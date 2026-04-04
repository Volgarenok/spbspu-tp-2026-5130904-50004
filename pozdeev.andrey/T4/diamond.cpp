#include "diamond.hpp"

namespace pozdeev {

Diamond::Diamond(double diagonalX, double diagonalY, const point_t& center)
  : diagX_{diagonalX}, diagY_{diagonalY}, center_{center}
{}

double Diamond::getArea() const
{
  return diagX_ * diagY_ / 2.0;
}

rectangle_t Diamond::getFrameRect() const
{
  rectangle_t rect;
  rect.width_ = diagX_;
  rect.height_ = diagY_;
  rect.pos_ = center_;
  return rect;
}

}
