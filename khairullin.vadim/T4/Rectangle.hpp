#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP
#include "Shape.hpp"

namespace khairullin
{
  struct Rectangle: Shape
  {
    double width, length;
    Rectangle(point_t p, double a, double b);
    virtual double getArea();
    virtual rectangle_t getFrameRect();
    virtual void move(point_t p);
    virtual void scale(double k);
    virtual ~Rectangle() = default;
  };
}
#endif
