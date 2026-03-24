#ifndef SHAPE_HPP
#define SHAPE_HPP

#include "point_t.hpp"
#include "rectangle_t.hpp"

namespace haliullin
{
  class Shape
  {
  public:
    virtual ~Shape() = default;

    virtual double getArea() const;
    virtual rectangle_t getFrameRect() const;

    virtual void move(const point_t & newPos);
    virtual void move(double dx, double dy);

    virtual void scale(double k);
  };
}


#endif
