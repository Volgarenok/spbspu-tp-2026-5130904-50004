#include "functions.hpp"
#include <iostream>
#include <iomanip>
#include <limits>
#include <cmath>

namespace haliullin
{
  point_t getRightBottomFrame(const rectangle_t & frame)
  {
    double halfWidth = frame.width / 2.0;
    double halfHeight = frame.height / 2.0;
    return point_t(frame.pos.x + halfWidth, frame.pos.y + halfHeight);
  }

  void displayFigure(const std::weak_ptr< Shape > & figure, const std::string & name, size_t id)
  {
    auto shape = figure.lock();
    if (!shape)
    {
      throw std::runtime_error("Expired weak pointer");
    }
    rectangle_t frame = shape->getFrameRect();
    std::cout << id << ". " << name << "\n";
    std::cout << "area = " << shape->getArea() << "\n";
    std::cout << "frame: center(" << frame.pos.x << ";" << frame.pos.y << "), width = "
    << frame.width << ", height = " << frame.height << "\n";
  }

}
