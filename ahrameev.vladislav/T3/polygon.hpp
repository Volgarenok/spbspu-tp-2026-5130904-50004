#ifndef AHRAMEEV_POLYGON_HPP
#define AHRAMEEV_POLYGON_HPP

#include <vector>

namespace ahrameev
{

  struct Point
  {
    int x;
    int y;
  };

  struct Polygon
  {
    std::vector< Point > points;
  };

}

#endif