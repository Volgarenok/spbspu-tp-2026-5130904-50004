#include <iostream>
#include <vector>
#include <memory>
#include <stdexcept>

#include "base-types.hpp"
#include "shape.hpp"
#include "rectangle.hpp"
#include "square.hpp"
#include "xquare.hpp"

namespace alberto {

bool scaleRelativeTo(const std::vector<std::shared_ptr<alberto::Shape>>& shapes)
{
  std::cout << "Enter scaling point and factor (px py factor): ";
  double px = 0.0, py = 0.0, factor = 0.0;
  if (!(std::cin >> px >> py >> factor)) {
    std::cerr << "Error: invalid input\n";
    return false;
  }
  if (factor <= 0.0) {
    std::cerr << "Error: scaling factor must be positive, got " << factor << "\n";
    return false;
  }
  point_t p = { px, py };
  for (const auto& shape : shapes) {
    point_t center = shape->getFrameRect().pos;
    double dx = (p.x - center.x) * (factor - 1.0);
    double dy = (p.y - center.y) * (factor - 1.0);
    shape->move(dx, dy);
    shape->scale(factor);
  }
  std::cout << "\n=== After scaling (point=(" << px << "," << py << ") factor=" << factor << ") ===\n";
  return true;
}

void printShapeInfo(const std::shared_ptr<Shape>& s, const std::string& name)
{
  rectangle_t fr = s->getFrameRect();
  std::cout << name
            << "  area=" << s->getArea()
            << "  frame=["
            << "pos=(" << fr.pos.x << "," << fr.pos.y << ")"
            << " w=" << fr.width
            << " h=" << fr.height
            << "]\n";
}

rectangle_t overallFrame(const std::vector<std::shared_ptr<Shape>>& shapes)
{
  double minX =  1e18, minY =  1e18;
  double maxX = -1e18, maxY = -1e18;
  for (const auto& s : shapes) {
    rectangle_t fr = s->getFrameRect();
    double left   = fr.pos.x - fr.width  / 2.0;
    double right  = fr.pos.x + fr.width  / 2.0;
    double bottom = fr.pos.y - fr.height / 2.0;
    double top    = fr.pos.y + fr.height / 2.0;
    if (left   < minX) minX = left;
    if (right  > maxX) maxX = right;
    if (bottom < minY) minY = bottom;
    if (top    > maxY) maxY = top;
  }
  double w = maxX - minX;
  double h = maxY - minY;
  point_t c = { (minX + maxX) / 2.0, (minY + maxY) / 2.0 };
  return { w, h, c };
}
