#ifndef EM_POLYGON_HPP
#define EM_POLYGON_HPP

#include "point.hpp"
#include <vector>
#include <iosfwd>

namespace em {

struct Polygon {
  std::vector<Point> points;
};

std::istream& operator>>(std::istream& is, Polygon& poly);

}

#endif
