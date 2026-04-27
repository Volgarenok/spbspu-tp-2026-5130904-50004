#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP

#include "shape.hpp"
#include <iosfwd>
#include <string>
#include <vector>

namespace aydogan
{
  using ShapeArray = std::vector< ShapePtr >;

  rectangle_t getCommonFrame(const ShapeArray& shapes);
  void printShapeInfo(const WeakShape& shape, const std::string& name, std::ostream& out);
  void printAllInfo(const ShapeArray& shapes, const std::vector< std::string >& names, std::ostream& out);
  void scaleShapeRelativeToPoint(const WeakShape& shape, const point_t& point, double coefficient);
  void scaleAllShapes(const ShapeArray& shapes, const point_t& point, double coefficient);
}

#endif
