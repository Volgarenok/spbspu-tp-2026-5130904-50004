#include "rectangle.hpp"
#include "square.hpp"
#include "triangle.hpp"
#include "functions.hpp"

#include <exception>
#include <iostream>
#include <memory>
#include <vector>

int main()
{
  using namespace aydogan;

  ShapeArray shapes;
  std::vector< std::string > names;

  try
  {
    shapes.push_back(std::make_shared< Rectangle >(6.0, 3.0, point_t(0.0, 0.0)));
    names.push_back("rectangle");

    shapes.push_back(std::make_shared< Triangle >(
      point_t(-2.0, 1.0),
      point_t(1.0, 5.0),
      point_t(4.0, 1.0)
    ));
    names.push_back("triangle");

    shapes.push_back(std::make_shared< Square >(4.0, point_t(5.0, -1.0)));
    names.push_back("square");
  }
  catch (const std::exception& e)
  {
    std::cerr << "creation error: " << e.what() << "\n";
    return 1;
  }

  double x = 0.0;
  double y = 0.0;
  double coefficient = 0.0;

  std::cin >> x >> y >> coefficient;

  if (!std::cin)
  {
    std::cerr << "input error\n";
    return 1;
  }

  if (coefficient <= 0.0)
  {
    std::cerr << "invalid scale coefficient\n";
    return 1;
  }

  return 0;
}
