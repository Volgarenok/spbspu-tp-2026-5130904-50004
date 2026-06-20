#include "rectangle_shape.hpp"
#include "xquare.hpp"
#include "complexquad.hpp"
#include "functions.hpp"
#include <iostream>
#include <vector>
#include <memory>
#include <array>

int main()
{
  try
  {
    std::vector<std::shared_ptr<velizade::Shape>> shapes;
    shapes.push_back(std::make_shared<velizade::Rectangle>(velizade::point_t{0, 0}, 4.0, 2.0));
    shapes.push_back(std::make_shared<velizade::Xsquare>(velizade::point_t{5, 5}, 3.0));
    shapes.push_back(std::make_shared<velizade::Complexquad>(
      std::array<velizade::point_t, 4>{
        velizade::point_t{-2,  1},
        velizade::point_t{ 2, -1},
        velizade::point_t{ 2,  1},
        velizade::point_t{-2, -1}
      }
    ));

    std::cout << "Before scaling:" << "\n";
    velizade::printAllInfo(shapes);

    double x, y, k;
    if (!(std::cin >> x >> y >> k))
    {
      return 0;
    }
    if (k <= 0)
    {
      std::cerr << "Scale factor must be positive" << "\n";
      return 1;
    }

    velizade::point_t pivot{x, y};
    velizade::scaleShapes(shapes, pivot, k);

    std::cout << "After scaling:" << "\n";
    velizade::printAllInfo(shapes);

  }
  catch (const std::exception& e)
  {
    std::cerr << "Error: " << e.what() << "\n";
    return 1;
  }

  return 0;
}
