#include "shape.hpp"
#include "rectangle.hpp"
#include "triangle.hpp"
#include "diamond.hpp"
#include "functions.hpp"

#include <string>
#include <vector>
#include <iostream>

using namespace aushev;

int main()
{
  std::vector<std::shared_ptr<Shape>> shps;
  std::vector<std::string> nms;

  try
  {
    shps.push_back(std::make_shared<Rectangle>(7.0, 2.8, point_t(1.0, 2.0)));
    nms.push_back("Rectangle");

    shps.push_back(std::make_shared<Triangle>(point_t(0.0, 0.0), point_t(4.0, 0.0), point_t(2.0, 3.0)));
    nms.push_back("Triangle");

    shps.push_back(std::make_shared<Diamond>(6.0, 4.0, point_t(5.0, 5.0)));
    nms.push_back("Diamond");
  }
  catch (const std::exception& err)
  {
    std::cerr << "Failed to create figures: " << err.what() << "\n";
    return 1;
  }

  std::vector<std::weak_ptr<Shape>> wshps;
  for (const auto& sh : shps)
  {
    wshps.push_back(sh);
  }

  std::cout << "BEFORE:\n\n";
  try
  {
    displayAll(wshps, nms);
    displayTotalFrame(getTotalFrame(wshps));
  }
  catch (const std::exception& err)
  {
    std::cerr << "Failed to display figures: " << err.what() << "\n";
    return 1;
  }
  std::cout << "\n";

  double x, y, k;
  std::cout << "Enter scale point (x y): ";
  if (!(std::cin >> x >> y))
  {
    if (std::cin.eof())
    {
      return 0;
    }
    std::cerr << "Invalid point coordinates\n";
    return 1;
  }

  std::cout << "Enter scale coefficient: ";
  if (!(std::cin >> k))
  {
    if (std::cin.eof())
    {
      return 0;
    }
    std::cerr << "Invalid coefficient\n";
    return 1;
  }

  if (k <= 0.0)
  {
    std::cerr << "Scale coefficient must be positive\n";
    return 1;
  }

  try
  {
    scaleFigures(wshps, point_t(x, y), k);
  }
  catch (const std::exception& err)
  {
    std::cerr << "Failed to scale figures: " << err.what() << "\n";
    return 1;
  }

  std::cout << "\nAFTER:\n\n";
  try
  {
    displayAll(wshps, nms);
    displayTotalFrame(getTotalFrame(wshps));
  }
  catch (const std::exception& err)
  {
    std::cerr << "Failed to display figures: " << err.what() << "\n";
    return 1;
  }

  return 0;
}
