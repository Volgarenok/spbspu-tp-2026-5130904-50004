#include "triangle.hpp"

namespace pozdeev {

Triangle::Triangle(double base, double height, const point_t& centroid)
  : base_{base}, height_{height}, centroid_{centroid}
{}

double Triangle::getArea() const
{
  return base_ * height_ / 2.0;
}

rectangle_t Triangle::getFrameRect() const
{
  rectangle_t rect;
  rect.width_ = base_;
  rect.height_ = height_;
  rect.pos_ = centroid_;
  return rect;
}

void Triangle::move(double dx, double dy)
{
  centroid_.x_ += dx;
  centroid_.y_ += dy;
}

void Triangle::move(const point_t& point)
{
  centroid_ = point;
}

void Triangle::scale(double coefficient)
{
  base_ *= coefficient;
  height_ *= coefficient;
}

}
