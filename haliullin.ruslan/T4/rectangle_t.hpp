#ifndef RECTANGLE_T_HPP
#define RECTANGLE_T_HPP

#include "point_t.hpp"

namespace haliullin
{
  struct rectangle_t
  {
    double width = 0.0;
    double height = 0.0;
    point_t pos = {0.0, 0.0};

    rectangle_t() = default;

    rectangle_t(double w, double h, const point_t & p) :
      width(w), height(h), pos(p)
    {}
  };
}

#endif
