#include <iostream>
#include <memory>
#include <vector>

#include "shape.hpp"
#include "rectangle.hpp"
#include "diamond.hpp"
#include "triangle.hpp"
#include "utils.hpp"

int main()
{
  std::vector<std::shared_ptr<pozdeev::Shape>> shapes;
  shapes.emplace_back(std::make_shared<pozdeev::Rectangle>(10.0, 5.0, pozdeev::point_t(0.0, 0.0)));
  shapes.emplace_back(std::make_shared<pozdeev::Diamond>(8.0, 6.0, pozdeev::point_t(5.0, 5.0)));
  shapes.emplace_back(std::make_shared<pozdeev::Triangle>(12.0, 9.0, pozdeev::point_t(-3.0, 4.0)));

  std::cout << "Initial state:\n";
  pozdeev::printShapesInfo(shapes);

  double pointX = 0.0;
  double pointY = 0.0;
  double scaleFactor = 0.0;

  std::cin >> pointX >> pointY >> scaleFactor;

  if (!std::cin)
  {
    if (std::cin.eof())
    {
      return 0;
    }
    std::cerr << "Error: invalid input.\n";
    return 1;
  }

  if (scaleFactor <= 0.0)
  {
    std::cerr << "Error: non-positive scale factor.\n";
    return 1;
  }

  pozdeev::point_t scalePoint(pointX, pointY);
  for (auto& shape : shapes)
  {
    pozdeev::scaleRelativeToPoint(shape, scalePoint, scaleFactor);
  }

  std::cout << "After scaling:\n";
  pozdeev::printShapesInfo(shapes);

  return 0;
}
