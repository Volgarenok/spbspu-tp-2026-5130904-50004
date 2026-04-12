#ifndef RING_H
#define RING_H

#include "Shape.h"

namespace nepochatova {

  class Ring : public Shape {
  private:
    point_t center_;
    double r_outer_;
    double r_inner_;

  public:
    Ring(point_t center, double r_outer, double r_inner);

    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void move(point_t newPos) override;
    void move(double dx, double dy) override;
    void scale(double k) override;
  };
}
#endif
