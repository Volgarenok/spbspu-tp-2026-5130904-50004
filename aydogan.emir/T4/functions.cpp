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

void aydogan::printShapeInfo(
  const WeakShape& weakShape,
  const std::string& name,
  std::ostream& out
)
{
  ShapePtr shape = weakShape.lock();
  if (!shape)
  {
    throw std::invalid_argument("Expired shape pointer");
  }

  rectangle_t frame = shape->getFrameRect();

  out << name << ":\n";
  out << "area = " << shape->getArea() << "\n";
  out << "frame center = (" << frame.pos_.x_ << "; " << frame.pos_.y_ << ")\n";
  out << "frame width = " << frame.width_ << "\n";
  out << "frame height = " << frame.height_ << "\n";
}

void aydogan::printAllInfo(
  const ShapeArray& shapes,
  const std::vector< std::string >& names,
  std::ostream& out
)
{
  if (shapes.size() != names.size())
  {
    throw std::invalid_argument("Invalid shape names count");
  }

  double totalArea = 0.0;

  out << std::fixed << std::setprecision(2);

  for (std::size_t i = 0; i < shapes.size(); ++i)
  {
    printShapeInfo(WeakShape(shapes[i]), names[i], out);
    totalArea += shapes[i]->getArea();
  }

  rectangle_t commonFrame = getCommonFrame(shapes);

  out << "total area = " << totalArea << "\n";
  out << "common frame center = (" << commonFrame.pos_.x_ << "; " << commonFrame.pos_.y_ << ")\n";
  out << "common frame width = " << commonFrame.width_ << "\n";
  out << "common frame height = " << commonFrame.height_ << "\n";
}
