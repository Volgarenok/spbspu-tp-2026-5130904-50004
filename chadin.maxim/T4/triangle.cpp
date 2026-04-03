#include "triangle.hpp"
#include <algorithm>
#include <cmath>
#include <stdexcept>

namespace chadin {
  Triangle::Triangle(point_t a, point_t b, point_t c):
    a_(a),
    b_(b),
    c_(c)
  {
    if (getArea() <= 0.0) {
      throw std::invalid_argument("Invalid triangle vertices");
    }
  }
