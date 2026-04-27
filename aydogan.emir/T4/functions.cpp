#include "functions.hpp"

#include <iomanip>
#include <limits>
#include <ostream>
#include <stdexcept>

namespace
{
  double getLeft(const aydogan::rectangle_t& frame)
  {
    return frame.pos_.x_ - frame.width_ / 2.0;
  }

  double getRight(const aydogan::rectangle_t& frame)
  {
    return frame.pos_.x_ + frame.width_ / 2.0;
  }

  double getBottom(const aydogan::rectangle_t& frame)
  {
    return frame.pos_.y_ - frame.height_ / 2.0;
  }

  double getTop(const aydogan::rectangle_t& frame)
  {
    return frame.pos_.y_ + frame.height_ / 2.0;
  }
}
