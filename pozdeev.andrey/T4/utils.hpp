#ifndef UTILS_HPP
#define UTILS_HPP

#include <memory>
#include <vector>
#include "shape.hpp"

namespace pozdeev {

void scaleRelativeToPoint(
  std::weak_ptr<Shape> shapeWeak,
  const point_t& point,
  double coefficient);

void printShapesInfo(const std::vector<std::shared_ptr<Shape>>& shapes);

}

#endif
