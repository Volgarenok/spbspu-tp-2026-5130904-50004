#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "Shape.h"
#include <vector>
#include <memory>
#include <iostream>
#include <limits>

namespace nepochatova {
  void scaleRelativeTo(std::weak_ptr<Shape> figure, point_t target, double k);
  double getTotalArea(const std::vector<std::weak_ptr<Shape>>& figures);
  rectangle_t getOverallFrame(const std::vector<std::weak_ptr<Shape>>& figures);
  void printFigureInfo(const std::weak_ptr<Shape>& fig, int id);
  void printAllFigures(const std::vector<std::weak_ptr<Shape>>& figures);
}

#endif
