#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "Shape.h"

namespace nepochatova {

  class Rectangle : public Shape {
  private:
    point_t pos_;
    double width_;
    double height_;

  public:
    Rectangle();
    Rectangle(const point_t& pos, double width, double height);

    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void move(point_t newPos) override;
    void move(double dx, double dy) override;
    void scale(double k) override;
  };
}

#endif
