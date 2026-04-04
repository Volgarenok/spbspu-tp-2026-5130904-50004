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
