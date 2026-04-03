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
  if (k <= 0)
  {
    std::cerr << "k must be a positive number\n";
    return 1;
  }

  point_t scale_pos{x, y};
  point_t pos_square{3, -3};
  double width = 4;
  double length = 4;

  point_t pos_romb{0, 1};
  double vertDiag = 4;
  double horDiag = 2;

  std::vector<point_t> points = {point_t{-3, 0}, point_t{-2, -4}, point_t{-7, -3}, point_t{-7, 2}, point_t{-5, 2}};
  std::vector<std::shared_ptr<Shape>> shapes;
  std::shared_ptr<Shape> square = nullptr;
  std::shared_ptr<Shape> romb = nullptr;
  std::shared_ptr<Shape> polygon = nullptr;
  try
  {
    square = std::make_shared<Rectangle>(pos_square, width, length);
    romb = std::make_shared<Diamond>(pos_romb, vertDiag, horDiag);
    polygon = std::make_shared<Polygon>(points);
  }
  catch (...)
  {
    std::cerr << "Bad alloc\n";
    return 2;
  }
  shapes.push_back(square);
  shapes.push_back(romb);
  shapes.push_back(polygon);

  std::vector<std::weak_ptr<Shape>> weak_shapes(shapes.begin(), shapes.end());
  output(weak_shapes);
  for (size_t i = 0; i < shapes.size(); i++)
  {
    double new_x = scale_pos.x - k * (scale_pos.x - shapes[i]->pos.x);
    double new_y = scale_pos.y - k * (scale_pos.y - shapes[i]->pos.y);
    point_t new_center{new_x, new_y};
    shapes[i]->move(new_center);
    shapes[i]->scale(k);
  }
  std::vector<std::weak_ptr<Shape>> new_weak_shapes(shapes.begin(), shapes.end());
  output(new_weak_shapes);
}
