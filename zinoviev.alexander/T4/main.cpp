#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include <cstdlib>

#include "rectangle.hpp"
#include "circle.hpp"
#include "polygon.hpp"
#include "function.hpp"

int main()
{
	using namespace zinoviev;
  try
  {
		std::vector< std::shared_ptr< Shape > > shapes;
    std::vector< std::string > names;

    shapes.push_back(std::make_shared< Rectangle >(point_t{ 0, 0 }, 4, 2));
    names.push_back("Rectangle");

    shapes.push_back(std::make_shared< Circle >(point_t{ 2, 1 }, 3));
    names.push_back("Circle");

    std::vector< point_t > polyPts = { {0,0}, {3,0}, {1.5,2.5}, {6.1, -6.1}, {10.8, 4.5} };
    shapes.push_back(std::make_shared< Polygon >(polyPts));
    names.push_back("Polygon");

    std::vector< std::weak_ptr< Shape > > weakShapes;
    for (const auto& s : shapes)
    	weakShapes.push_back(s);

		std::cout << "BEFORE SCALING:\n";
    printAllFigures(weakShapes, names);
    rectangle_t totalFrame = getAllFrameRect(weakShapes);
    printTotalFrame(totalFrame);

    point_t scaleCenter;
    double k;

    std::cout << "Enter scaling point (x;y): ";
    if (!(std::cin >> scaleCenter.x >> scaleCenter.y))
    {
    	std::cerr << "Error: invalid point\n";
      return 1;
    }

    std::cout << "Enter scaling factor (k > 0): ";
    if (!(std::cin >> k) || k <= 0)
    {
    	std::cerr << "Error: factor must be positive\n";
      return 1;
    }

    scaleAllFigures(weakShapes, scaleCenter, k);

    std::cout << "AFTER SCALING:\n";
    printAllFigures(weakShapes, names);
    totalFrame = getAllFrameRect(weakShapes);
    printTotalFrame(totalFrame);
	}
  catch (const std::exception& e)
  {
  	std::cerr << "Error: " << e.what() << std::endl;
    return 1;
  }
}
