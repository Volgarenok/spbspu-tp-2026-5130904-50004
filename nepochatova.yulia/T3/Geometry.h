#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <vector>
#include <iostream>

namespace nepochatova {
  struct Point {
    int x, y;

    bool operator==(const Point &other) const;
  };

  struct Polygon {
    std::vector<Point> points;

    double area() const;
    bool operator==(const Polygon &other) const;
  };

  struct PointIO {
    Point &ref;
  };

  std::istream &operator>>(std::istream &in, PointIO &&dest);
  std::istream &operator>>(std::istream &in, Polygon &poly);

}
#endif
