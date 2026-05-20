#include <iostream>
#include <memory>
#include <vector>

#include "rectangle.hpp"
#include "triangle.hpp"
#include "concave.hpp"

void printInfo(const std::shared_ptr< ali::Shape > & shape)
{
  ali::rectangle_t rect = shape->getFrameRect();

  std::cout << "Area: " << shape->getArea() << '\n';

  std::cout << "Frame: "
            << rect.width
            << ' '
            << rect.height
            << ' '
            << rect.pos.x
            << ' '
            << rect.pos.y
            << '\n';
}

int main()
{
  using namespace ali;

  std::vector< std::shared_ptr< Shape > > shapes;

  shapes.push_back(
    std::make_shared< Rectangle >(
      10.0,
      5.0,
      point_t{0.0, 0.0}));

  shapes.push_back(
    std::make_shared< Triangle >(
      point_t{0.0, 0.0},
      point_t{5.0, 0.0},
      point_t{0.0, 5.0}));

  shapes.push_back(
    std::make_shared< Concave >(
      point_t{0.0, 0.0},
      point_t{4.0, 0.0},
      point_t{2.0, 1.0},
      point_t{0.0, 4.0}));

  std::cout << "Before scaling:\n";

  for (const auto & shape: shapes)
  {
    printInfo(shape);
  }

  double x = 0.0;
  double y = 0.0;
  double k = 1.0;

  std::cout << "Input center x y and scale:\n";

  std::cin >> x >> y >> k;

  if (!std::cin || k <= 0)
  {
    std::cerr << "error\n";
    return 1;
  }

  point_t center{ x, y };

  for (const auto & shape: shapes)
  {
    rectangle_t rect = shape->getFrameRect();

    double dx = rect.pos.x - center.x;
    double dy = rect.pos.y - center.y;

    shape->move(dx * (k - 1), dy * (k - 1));
    shape->scale(k);
  }

  std::cout << "After scaling:\n";

  for (const auto & shape: shapes)
  {
    printInfo(shape);
  }

  return 0;
}
