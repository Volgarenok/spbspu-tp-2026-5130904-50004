#include "output.hpp"
#include "Point.hpp"
#include "Rec_t.hpp"
#include "Shape.hpp"
#include "Rectangle.hpp"
#include "Diamond.hpp"
#include "Polygon.hpp"
#include <iostream>
int main()
{
  double k = 0;
  double x = 0, y = 0;
  std::cin >> x >> y >> k;
  if (k < 0)
  {
    std::cerr << "k must be a positive number\n";
    return 1;
  }

  khairullin::point_t scale_pos{x, y};
  khairullin::point_t pos_square{3, -3};
  double width = 4;
  double length = 4;

  khairullin::point_t pos_romb{0, 1};
  double vertDiag = 4;
  double horDiag = 2;

  std::vector< khairullin::point_t > points = {khairullin::point_t{-3, 0}, khairullin::point_t{-2, -4}, 
    khairullin::point_t{-7, -3}, khairullin::point_t{-7, 2}, khairullin::point_t{-5, 2}};
  std::vector< std::shared_ptr< khairullin::Shape > > shapes;
  std::shared_ptr< khairullin::Shape > square = nullptr;
  std::shared_ptr< khairullin::Shape > romb = nullptr;
  std::shared_ptr< khairullin::Shape > polygon = nullptr;
  try
  {
    square = std::make_shared< khairullin::Rectangle >(pos_square, width, length);
    romb = std::make_shared< khairullin::Diamond >(pos_romb, vertDiag, horDiag);
    polygon = std::make_shared< khairullin::Polygon >(points);
  }
  catch (...)
  {
    std::cerr << "Bad alloc\n";
    return 2;
  }
  shapes.push_back(square);
  shapes.push_back(romb);
  shapes.push_back(polygon);

  std::vector< std::weak_ptr< khairullin::Shape > > weak_shapes(shapes.begin(), shapes.end());
  try
  { 
    output(weak_shapes);
  }
  catch (const std::logic_error & error)
  {
    std::cerr << error.what() << "\n";
    return 1;
  }
  for (size_t i = 0; i < shapes.size(); i++)
  {
    double new_x = scale_pos.x - k * (scale_pos.x - shapes[i]->pos.x);
    double new_y = scale_pos.y - k * (scale_pos.y - shapes[i]->pos.y);
    khairullin::point_t new_center{new_x, new_y};
    shapes[i]->move(new_center);
    shapes[i]->scale(k);
  }
  std::vector< std::weak_ptr< khairullin::Shape > > new_weak_shapes(shapes.begin(), shapes.end());
  try
  {
    output(new_weak_shapes);
  }
  catch (const std::logic_error & error)
  { 
    std::cerr << error.what() << "\n"; 
    return 1;
  }
}
