#ifndef POD_H
#define POD_H

struct point_t {
  double x, y;

  point_t() = default;

  point_t(double i, double j):
    x(i), y(j) {}
};

struct rectangle_t {
  double width, height;
  point_t pos;

  rectangle_t() = default;

  rectangle_t(double w, double h, point_t p):
    width(w), height(h), pos(p) {}
};

#endif
