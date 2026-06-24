#ifndef EM_POLYGON_HPP
#define EM_POLYGON_HPP

#include "point.hpp"
#include <vector>

namespace em {

struct Polygon {
  std::vector<Point> points;
};

}

#endif
