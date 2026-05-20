#ifndef POLYGON_H
#define POLYGON_H

#include <iostream>
#include <vector>

namespace alekseev {
  struct Point {
    int x, y;
  };

  std::istream & operator>>(std::istream & is, Point p);
  std::ostream & operator<<(std::ostream & os, const Point & p);

  struct Polygon {
    std::vector< Point > points;
  };

  std::istream & operator>>(std::istream & is, Polygon & p);
  std::ostream & operator<<(std::ostream & os, const Polygon & p);
}

#endif
