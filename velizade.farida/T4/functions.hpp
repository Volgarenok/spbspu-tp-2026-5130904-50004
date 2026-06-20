#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP

#include "rectangle.hpp"
#include <vector>
#include <memory>

namespace velizade
{
  rectangle_t getCommonFrameRect(const std::vector<std::shared_ptr<Shape>>& shapes);
  void printShapeInfo(const std::weak_ptr<Shape>& wptr);
  void printAllInfo(const std::vector<std::shared_ptr<Shape>>& shapes);
  void scaleShapes(std::vector<std::shared_ptr<Shape>>& shapes, const point_t& pivot, double k);
}

#endif
