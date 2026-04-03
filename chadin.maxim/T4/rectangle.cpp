#include "rectangle.hpp"
#include <stdexcept>

namespace chadin {
  Rectangle::Rectangle(double width, double height, point_t pos):
    width_(width),
    height_(height),
    pos_(pos)
  {
    if (width <= 0.0 || height <= 0.0) {
      throw std::invalid_argument("Invalid rectangle dimensions");
    }
  }
