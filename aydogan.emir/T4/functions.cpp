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

aydogan::rectangle_t aydogan::getCommonFrame(const ShapeArray& shapes)
{
  if (shapes.empty())
  {
    return rectangle_t();
  }

  double left = std::numeric_limits< double >::max();
  double right = std::numeric_limits< double >::lowest();
  double bottom = std::numeric_limits< double >::max();
  double top = std::numeric_limits< double >::lowest();

  bool hasShape = false;

  for (const ShapePtr& shape: shapes)
  {
    if (!shape)
    {
      continue;
    }

    rectangle_t frame = shape->getFrameRect();

    if (getLeft(frame) < left)
    {
      left = getLeft(frame);
    }
    if (getRight(frame) > right)
    {
      right = getRight(frame);
    }
    if (getBottom(frame) < bottom)
    {
      bottom = getBottom(frame);
    }
    if (getTop(frame) > top)
    {
      top = getTop(frame);
    }

    hasShape = true;
  }

  if (!hasShape)
  {
    return rectangle_t();
  }

  return rectangle_t(
    right - left,
    top - bottom,
    point_t((left + right) / 2.0, (bottom + top) / 2.0)
  );
}
