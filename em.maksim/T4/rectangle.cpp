#include "rectangle.hpp"

#include <stdexcept>

namespace em {

Rectangle::Rectangle(point_t center, double width, double height)
  : center_{center}
{
  if (width <= 0.0 || height <= 0.0) {
    throw std::invalid_argument("Invalid rectangle dimensions");
  }
  width_ = width;
  height_ = height;
}

}
