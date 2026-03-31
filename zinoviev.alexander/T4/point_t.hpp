#ifndef POINT_T_HPP

#define POINT_T_HPP

namespace zinoviev
{
  struct point_t
  {
    double x;
    double y;

    point_t() :
      x(0.0),
      y(0.0)
    {}

    point_t(double a, double b) :
      x(a),
      y(b)
    {}
  };
}
#endif
