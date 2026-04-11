#ifndef POD_H
#define POD_H

namespace nepochatova {

  struct point_t {
    double x = 0.0;
    double y = 0.0;
    point_t() = default;
    point_t(double x_, double y_) : x(x_), y(y_) {}
  };

  struct rectangle_t {
    double width = 0.0;
    double height = 0.0;
    point_t pos;
    rectangle_t() = default;
    rectangle_t(double w, double h, point_t p)
        : width(w), height(h), pos(p) {}
  };
}
#endif