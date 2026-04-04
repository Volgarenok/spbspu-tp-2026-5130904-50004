#include "complexquad.hpp"
#include "rectangle.hpp"
#include "shape.hpp"

#include <iostream>
#include <limits>
#include <memory>
#include <vector>

namespace em {

void printStats(const std::vector<std::shared_ptr<Shape>>& shapes)
{
  double total_area = 0.0;
  double global_min_x = std::numeric_limits<double>::max();
  double global_max_x = std::numeric_limits<double>::lowest();
  double global_min_y = std::numeric_limits<double>::max();
  double global_max_y = std::numeric_limits<double>::lowest();

  for (const auto& shape : shapes) {
    double area = shape->getArea();
    total_area += area;

    rectangle_t frame = shape->getFrameRect();
    double half_w = frame.width_ / 2.0;
    double half_h = frame.height_ / 2.0;

    double min_x = frame.pos_.x_ - half_w;
    double max_x = frame.pos_.x_ + half_w;
    double min_y = frame.pos_.y_ - half_h;
    double max_y = frame.pos_.y_ + half_h;

    if (min_x < global_min_x) global_min_x = min_x;
    if (max_x > global_max_x) global_max_x = max_x;
    if (min_y < global_min_y) global_min_y = min_y;
    if (max_y > global_max_y) global_max_y = max_y;

    std::cout << "Area: " << area << "\n";
    std::cout << "Frame: pos(" << frame.pos_.x_ << ", " << frame.pos_.y_
              << ") size(" << frame.width_ << "x" << frame.height_ << ")\n";
  }

  std::cout << "Total Area: " << total_area << "\n";
  double global_w = global_max_x - global_min_x;
  double global_h = global_max_y - global_min_y;
  std::cout << "Overall Frame: pos(" << (global_min_x + global_max_x) / 2.0 << ", "
            << (global_min_y + global_max_y) / 2.0 << ") size(" << global_w << "x" << global_h << ")\n";
}

void scaleAroundPoint(std::weak_ptr<Shape> shape_weak, point_t ref_point, double factor)
{
  auto shape = shape_weak.lock();
  if (!shape) {
    return;
  }

  point_t current_center = shape->getFrameRect().pos_;
  double dx = (factor - 1.0) * (current_center.x_ - ref_point.x_);
  double dy = (factor - 1.0) * (current_center.y_ - ref_point.y_);

  shape->move(dx, dy);
  shape->scale(factor);
}

}
