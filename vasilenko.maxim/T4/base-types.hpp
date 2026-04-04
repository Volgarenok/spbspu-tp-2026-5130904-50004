#ifndef VASILENKO_BASE_TYPES_HPP
#define VASILENKO_BASE_TYPES_HPP

namespace vasilenko
{
  struct point_t
  {
    double x;
    double y;
  };

  struct rectangle_t
  {
    double width;
    double height;
    point_t pos;
  };
}

#endif
