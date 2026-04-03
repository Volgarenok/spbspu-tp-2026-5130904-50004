#include "complexquad.hpp"
#include "rectangle.hpp"
#include "shape.hpp"
#include "triangle.hpp"
#include <algorithm>
#include <iostream>
#include <limits>
#include <memory>
#include <vector>

namespace {
  chadin::rectangle_t getTotalFrameRect(const std::vector<std::shared_ptr<chadin::Shape>>& shapes)
  {
    if (shapes.empty()) {
      return {0.0, 0.0, {0.0, 0.0}};
    }
    double min_x = std::numeric_limits<double>::max();
    double max_x = std::numeric_limits<double>::lowest();
    double min_y = std::numeric_limits<double>::max();
    double max_y = std::numeric_limits<double>::lowest();

    for (const auto& shape: shapes) {
      const chadin::rectangle_t rect = shape->getFrameRect();
      min_x = std::min(min_x, rect.pos.x - rect.width / 2.0);
      max_x = std::max(max_x, rect.pos.x + rect.width / 2.0);
      min_y = std::min(min_y, rect.pos.y - rect.height / 2.0);
      max_y = std::max(max_y, rect.pos.y + rect.height / 2.0);
    }
    return {max_x - min_x, max_y - min_y, {(min_x + max_x) / 2.0, (min_y + max_y) / 2.0}};
  }

  void printShapesInfo(const std::vector<std::shared_ptr<chadin::Shape>>& shapes)
  {
    double total_area = 0.0;
    for (const auto& shape: shapes) {
      const double area = shape->getArea();
      total_area += area;
      const chadin::rectangle_t rect = shape->getFrameRect();
      std::cout << area << "\n" << rect.width << " " << rect.height << " " << rect.pos.x << " " << rect.pos.y << "\n";
    }
    std::cout << total_area << "\n";
    const chadin::rectangle_t total_rect = getTotalFrameRect(shapes);
    std::cout << total_rect.width << " " << total_rect.height << " " << total_rect.pos.x << " " << total_rect.pos.y << "\n";
  }

  void scaleShape(std::weak_ptr<chadin::Shape> weak_shape, chadin::point_t scale_center, double coef)
  {
    if (const auto shape = weak_shape.lock()) {
      const chadin::point_t bb_before = shape->getFrameRect().pos;
      shape->scale(coef);
      const chadin::point_t bb_after = shape->getFrameRect().pos;
      const double dx = (scale_center.x + (bb_before.x - scale_center.x) * coef) - bb_after.x;
      const double dy = (scale_center.y + (bb_before.y - scale_center.y) * coef) - bb_after.y;
      shape->move(dx, dy);
    }
  }
}
