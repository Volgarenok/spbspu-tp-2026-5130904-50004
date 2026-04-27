#include "triangle.hpp"
#include <algorithm>
#include <cmath>
#include <stdexcept>

namespace
{
  double getSignedArea(
    const aydogan::point_t& first,
    const aydogan::point_t& second,
    const aydogan::point_t& third
  )
  {
    return (
      first.x_ * (second.y_ - third.y_) +
      second.x_ * (third.y_ - first.y_) +
      third.x_ * (first.y_ - second.y_)
    ) / 2.0;
  }

  aydogan::point_t getCenter(
    const aydogan::point_t& first,
    const aydogan::point_t& second,
    const aydogan::point_t& third
  )
  {
    return aydogan::point_t(
      (first.x_ + second.x_ + third.x_) / 3.0,
      (first.y_ + second.y_ + third.y_) / 3.0
    );
  }
}

aydogan::Triangle::Triangle(const point_t& first, const point_t& second, const point_t& third):
  first_(first),
  second_(second),
  third_(third),
  center_(getCenter(first, second, third))
{
  if (std::abs(getSignedArea(first_, second_, third_)) == 0.0)
  {
    throw std::invalid_argument("Invalid triangle points");
  }
}

double aydogan::Triangle::getArea() const
{
  return std::abs(getSignedArea(first_, second_, third_));
}

aydogan::rectangle_t aydogan::Triangle::getFrameRect() const
{
  double minX = std::min(std::min(first_.x_, second_.x_), third_.x_);
  double maxX = std::max(std::max(first_.x_, second_.x_), third_.x_);
  double minY = std::min(std::min(first_.y_, second_.y_), third_.y_);
  double maxY = std::max(std::max(first_.y_, second_.y_), third_.y_);

  double width = maxX - minX;
  double height = maxY - minY;
  point_t pos((minX + maxX) / 2.0, (minY + maxY) / 2.0);

  return rectangle_t(width, height, pos);
}

void aydogan::Triangle::move(const point_t& point)
{
  double dx = point.x_ - center_.x_;
  double dy = point.y_ - center_.y_;
  move(dx, dy);
}

void aydogan::Triangle::move(double dx, double dy)
{
  first_.x_ += dx;
  first_.y_ += dy;

  second_.x_ += dx;
  second_.y_ += dy;

  third_.x_ += dx;
  third_.y_ += dy;

  center_.x_ += dx;
  center_.y_ += dy;
}

void aydogan::Triangle::scale(double coefficient)
{
  if (coefficient <= 0.0)
  {
    throw std::invalid_argument("Invalid scale coefficient");
  }

  first_.x_ = center_.x_ + (first_.x_ - center_.x_) * coefficient;
  first_.y_ = center_.y_ + (first_.y_ - center_.y_) * coefficient;

  second_.x_ = center_.x_ + (second_.x_ - center_.x_) * coefficient;
  second_.y_ = center_.y_ + (second_.y_ - center_.y_) * coefficient;

  third_.x_ = center_.x_ + (third_.x_ - center_.x_) * coefficient;
  third_.y_ = center_.y_ + (third_.y_ - center_.y_) * coefficient;
}
