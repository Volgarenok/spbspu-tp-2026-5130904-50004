#ifndef EM_SHAPE_HPP
#define EM_SHAPE_HPP

#include "basic-types.hpp"

namespace em {

class Shape
{
public:
  virtual ~Shape() = default;

  virtual double getArea() const = 0;
  virtual rectangle_t getFrameRect() const = 0;
  virtual void move(point_t dest) = 0;
  virtual void move(double dx, double dy) = 0;
  virtual void scale(double factor) = 0;
};

}

#endif
