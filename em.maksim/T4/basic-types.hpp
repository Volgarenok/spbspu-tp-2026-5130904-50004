#ifndef EM_BASIC_TYPES_HPP
#define EM_BASIC_TYPES_HPP

namespace em {

struct point_t
{
  double x_{0.0};
  double y_{0.0};
};

struct rectangle_t
{
  double width_{0.0};
  double height_{0.0};
  point_t pos_{0.0, 0.0};
};

}

#endif
