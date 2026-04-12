#include "rectangle.h"
#include "bubble.h"
#include "ring.h"
#include "functions.h"
#include <iostream>
#include <vector>
#include <memory>

int main() {
  using namespace nepochatova;

  try {
    std::vector<std::shared_ptr<Shape> > shapes;
    shapes.push_back(std::make_shared<Rectangle>(point_t{0.0, 0.0}, 4.0, 6.0));
    shapes.push_back(std::make_shared<Bubble>(point_t{1.0, 1.0}, point_t{0.0, 0.0}, 5.0));
    shapes.push_back(std::make_shared<Ring>(point_t{-5.0, -2.0}, 6.0, 3.0));
    std::vector<std::weak_ptr<Shape> > weakShapes;
    for (const auto &shape: shapes) {
      weakShapes.push_back(shape);
    }

    std::cout << "Before scaling: " << std::endl;
    printAllFigures(weakShapes);

    rectangle_t overallFrame = getOverallFrame(weakShapes);
    std::cout << "Total frame: center (" << overallFrame.pos.x << "; "
        << overallFrame.pos.y << "), width = " << overallFrame.width
        << ", height = " << overallFrame.height << std::endl << std::endl;

    double px, py, k;
    if (!(std::cin >> px >> py >> k)) {
      std::cerr << "Error: invalid input format" << std::endl;
      return 1;
    }

    if (k <= 0.0) {
      std::cerr << "Error: scale coefficient must be positive" << std::endl;
      return 1;
    }

    point_t scalePoint{px, py};

    for (auto &weakShape: weakShapes) {
      scaleRelativeTo(weakShape, scalePoint, k);
    }

    std::cout << std::endl << "After scaling: " << std::endl;
    printAllFigures(weakShapes);

    overallFrame = getOverallFrame(weakShapes);
    std::cout << "Total frame: center (" << overallFrame.pos.x << "; "
        << overallFrame.pos.y << "), width = " << overallFrame.width
        << ", height = " << overallFrame.height << std::endl;

    return 0;
  } catch (const std::exception &e) {
    std::cerr << "Error: " << e.what() << std::endl;
    return 1;
  }
}

