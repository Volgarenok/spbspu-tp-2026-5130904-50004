#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP

#include "shape.hpp"
#include <vector>
#include <memory>
#include <string>

namespace haliullin
{
  point_t getRightBottomFrame(const rectangle_t & frame);
  void displayFigure(const std::weak_ptr< Shape > & figure, const std::string & name, size_t id);
  void displayAll(const std::vector< std::weak_ptr< Shape > > & figures, const std::vector< std::string > & names);
  rectangle_t getAllFrame(const std::vector< std::weak_ptr< Shape > > & figures);
  void displayAllFrame(const rectangle_t & frame);
  void scaleFigures(std::vector< std::weak_ptr< Shape > > & Figures, const point_t & scaleCenter, double coef);
}

#endif
