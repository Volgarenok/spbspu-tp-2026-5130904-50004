#ifndef BASE_TYPES_HPP
#define BASE_TYPES_HPP

namespace aydogan
{
  struct point_t
  {
    double x_;
    double y_;

    point_t():
      x_(0.0),
      y_(0.0)
    {}

    point_t(double x, double y):
      x_(x),
      y_(y)
    {}
  };

  struct rectangle_t
  {
  };
}

#endif

