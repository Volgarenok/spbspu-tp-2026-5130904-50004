#ifndef SHAPE_H
#define SHAPE_H
#include "POD.h"

class Shape {
public:
  virtual double getArea() = 0;
  virtual rectangle_t getFrameRect() = 0;

  virtual void move(const double& delta_x, const double& delta_y) = 0;
  virtual void move(const point_t& new_point) = 0;

  virtual void scale(const point_t& p, const double& k) = 0;
  ~Shape()=default;
};

#endif
