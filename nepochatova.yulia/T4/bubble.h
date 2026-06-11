#ifndef BUBBLE_H
#define BUBBLE_H

#include "Shape.h"
#include <cmath>

namespace nepochatova {

  class Bubble : public Shape {
  private:
    point_t pivot_;
    point_t geom_center_;
    double radius_;

  public:
    Bubble(point_t pivot, point_t geom_center, double radius);

    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void move(point_t newPos) override;
    void move(double dx, double dy) override;
    void scale(double k) override;
  };
}
#endif
