#ifndef RECTANGLE_H
#define RECTANGLE_H
#include "shape.h"

namespace alberto {

class Rectangle : public Shape {
public:
  Rectangle(const point_t& center, double width, double height);
  Rectangle(const point_t& bottomLeft, const point_t& topRight);

  double getArea() const override;
  rectangle_t getFrameRect() const override;
  void move(const point_t& dest) override;
  void move(double dx, double dy) override;
  void scale(double factor) override;

private:
  point_t center_;
  double width_;
  double height_;
};

}

#endif
