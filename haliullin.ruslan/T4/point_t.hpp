#ifndef POINT_T_HPP
#define POINT_T_HPP

namespace haliullin
{
  struct point_t
  {
    double x = 0.0;
    double y = 0.0;

    point_t() = default;

    point_t(double xx, double yy) :
      x(xx), y(yy)
    {}
  };
}

#endif
