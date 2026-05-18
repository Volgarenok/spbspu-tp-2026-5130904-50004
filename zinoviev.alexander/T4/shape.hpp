#ifndef SHAPE_HPP

#define SHAPE_HPP
#include "point_t.hpp"
#include "rectangle_t.hpp"

namespace zinoviev
{
  struct Shape
  {
    virtual double getArea() const = 0;
    virtual rectangle_t getFrameRect() const = 0;
    virtual void move(const point_t& newPos) = 0;
    virtual void move(double dx, double dy) = 0;
    virtual void scale(double k) = 0;
    virtual ~Shape() = default;
  };
}
#endif
