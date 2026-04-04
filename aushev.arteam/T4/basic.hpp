#ifndef BASIC_HPP
#define BASIC_HPP

namespace aushev
{
  struct point_t
  {
    double x_ = 0.0;
    double y_ = 0.0;

    point_t() = default;
    point_t(double x, double y): x_(x), y_(y) {}
  };

  struct rectangle_t
  {
    double width_ = 0.0;
    double height_ = 0.0;
    point_t pos_ = {0.0, 0.0};

    rectangle_t() = default;
    rectangle_t(double width, double height, point_t pos): width_(width), height_(height), pos_(pos) {}
  };
}

#endif
