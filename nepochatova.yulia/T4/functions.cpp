#include "functions.h"
#include <cstdlib>

namespace nepochatova {
  void scaleRelativeTo(std::weak_ptr<Shape> figureWeak, point_t target, double k) {
    auto figure = figureWeak.lock();

    if (!figure) return;

    if (k <= 0.0) {
      std::cerr << "Error: scale coefficient must be positive\n";
      std::exit(1);
    }

    point_t oldCenter = figure->getFrameRect().pos;

    double dx = oldCenter.x - target.x;
    double dy = oldCenter.y - target.y;

    figure->move(target);
    figure->scale(k);
    figure->move(point_t{target.x + dx * k, target.y + dy * k});
  }

  double getTotalArea(const std::vector<std::shared_ptr<Shape> > &figures) {
    double total = 0.0;
    for (const auto &fig: figures) {
      if (fig) total += fig->getArea();
    }
    return total;
  }

  rectangle_t getOverallFrame(const std::vector<std::shared_ptr<Shape> > &figures) {
    if (figures.empty()) {
      return rectangle_t{0.0, 0.0, point_t{0.0, 0.0}};
    }

    double minX = std::numeric_limits<double>::max();
    double maxX = std::numeric_limits<double>::lowest();
    double minY = std::numeric_limits<double>::max();
    double maxY = std::numeric_limits<double>::lowest();

    for (const auto &fig: figures) {
      if (!fig) continue;

      rectangle_t f = fig->getFrameRect();
      double left = f.pos.x - f.width / 2.0;
      double right = f.pos.x + f.width / 2.0;
      double bottom = f.pos.y - f.height / 2.0;
      double top = f.pos.y + f.height / 2.0;

      if (left < minX) minX = left;
      if (right > maxX) maxX = right;
      if (bottom < minY) minY = bottom;
      if (top > maxY) maxY = top;
    }

    double width = maxX - minX;
    double height = maxY - minY;
    return rectangle_t{width, height, point_t{(minX + maxX) / 2.0, (minY + maxY) / 2.0}};
  }

  void printFigureInfo(const std::shared_ptr<Shape> &fig, int id) {
    if (!fig) {
      std::cerr << "Figure " << id << ": null pointer\n";
      return;
    }

    rectangle_t f = fig->getFrameRect();
    std::cout << "Figure " << id << ":\n"
        << "  area = " << fig->getArea() << "\n"
        << "  frame: (" << f.pos.x << ";" << f.pos.y << "), width = "
        << f.width << ", height = " << f.height << "\n";
  }

  void printAllFigures(const std::vector<std::shared_ptr<Shape> > &figures) {
    double totalArea = 0.0;

    for (size_t i = 0; i < figures.size(); ++i) {
      printFigureInfo(figures[i], i + 1);
      if (figures[i]) {
        totalArea += figures[i]->getArea();
      }
    }

    std::cout << "\nTotal area = " << totalArea << "\n";

    rectangle_t overall = getOverallFrame(figures);
    std::cout << "Total frame: (" << overall.pos.x << ";" << overall.pos.y << ") "
        << "width = " << overall.width << ", height = " << overall.height << "\n";
  }
}
