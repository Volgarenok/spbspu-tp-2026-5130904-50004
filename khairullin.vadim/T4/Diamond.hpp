#ifndef DIAMOND_HPP
#define DIAMOND_HPP
#include "Shape.hpp"

struct Diamond: Shape
{
  double vertDiag, horDiag;
  Diamond(point_t p, double a, double b);
  virtual double getArea();
  virtual rectangle_t getFrameRect();
  virtual void move(point_t p);
  virtual void scale(double k);
  virtual ~Diamond() = default;
};

#endif
