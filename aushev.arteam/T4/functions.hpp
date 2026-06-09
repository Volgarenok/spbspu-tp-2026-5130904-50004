#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP

#include "shape.hpp"
#include <vector>
#include <memory>
#include <string>

namespace aushev
{
  void displayFigure(const std::weak_ptr<Shape>& fig, const std::string& nm, size_t id);
  void displayAll(const std::vector<std::weak_ptr<Shape>>& figs, const std::vector<std::string>& nms);
  rectangle_t getTotalFrame(const std::vector<std::weak_ptr<Shape>>& figs);
  void displayTotalFrame(const rectangle_t& fr);

  void scaleFigures(std::vector<std::weak_ptr<Shape>>& figs, const point_t& ctr, double k);
}

#endif
