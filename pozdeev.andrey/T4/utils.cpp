#include "utils.hpp"
#include <algorithm>
#include <iostream>

namespace pozdeev {

void scaleRelativeToPoint(
  std::weak_ptr<Shape> shapeWeak,
  const point_t& point,
  double coefficient)
{
  auto shape = shapeWeak.lock();
  if (!shape)
  {
    return;
  }

  rectangle_t frame = shape->getFrameRect();
  point_t oldCenter = frame.pos_;

  double newX = point.x_ + coefficient * (oldCenter.x_ - point.x_);
  double newY = point.y_ + coefficient * (oldCenter.y_ - point.y_);

  shape->move(newX - oldCenter.x_, newY - oldCenter.y_);
  shape->scale(coefficient);
}

void printShapesInfo(const std::vector<std::shared_ptr<Shape>>& shapes)
{
  if (shapes.empty())
  {
    return;
  }

  double totalArea = 0.0;
  rectangle_t firstFrame = shapes[0]->getFrameRect();
  double minX = firstFrame.pos_.x_ - firstFrame.width_ / 2.0;
  double maxX = firstFrame.pos_.x_ + firstFrame.width_ / 2.0;
  double minY = firstFrame.pos_.y_ - firstFrame.height_ / 2.0;
  double maxY = firstFrame.pos_.y_ + firstFrame.height_ / 2.0;

  for (std::size_t i = 0; i < shapes.size(); ++i)
  {
    rectangle_t frame = shapes[i]->getFrameRect();
    double area = shapes[i]->getArea();
    totalArea += area;

    std::cout << "Shape " << i + 1 << ":\n";
    std::cout << "  Area: " << area << "\n";
    std::cout << "  Frame Rect: pos(" << frame.pos_.x_ << ", " << frame.pos_.y_
              << "), w=" << frame.width_ << ", h=" << frame.height_ << "\n";

    double left = frame.pos_.x_ - frame.width_ / 2.0;
    double right = frame.pos_.x_ + frame.width_ / 2.0;
    double bottom = frame.pos_.y_ - frame.height_ / 2.0;
    double top = frame.pos_.y_ + frame.height_ / 2.0;

    minX = std::min(minX, left);
    maxX = std::max(maxX, right);
    minY = std::min(minY, bottom);
    maxY = std::max(maxY, top);
  }

  std::cout << "Total Area: " << totalArea << "\n";
  std::cout << "Overall Frame Rect: pos(" << (minX + maxX) / 2.0 << ", " << (minY + maxY) / 2.0
            << "), w=" << (maxX - minX) << ", h=" << (maxY - minY) << "\n\n";
}

}
