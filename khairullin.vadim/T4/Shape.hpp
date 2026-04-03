#define SHAPE_HPP
#ifndef SHAPE_HPP
#include "Rec_t.hpp"

struct Shape
{
  point_t pos;
  virtual double getArea() = 0;
  virtual rectangle_t getFrameRect() = 0;
  virtual void move(point_t p) = 0;
  virtual void scale(double k) = 0;
  virtual ~Shape() = default;
};

#endif
