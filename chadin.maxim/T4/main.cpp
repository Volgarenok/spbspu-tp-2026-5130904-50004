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
