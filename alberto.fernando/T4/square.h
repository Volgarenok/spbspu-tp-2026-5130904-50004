#ifndef SQUARE_H
#define SQUARE_H
#include "shape.h"

namespace alberto {
class Square : public Shape {
public:
  Square(const point_t& center, double side);

  double getArea() const override;
  rectangle_t getFrameRect() const override;
  void move(const point_t& dest) override;
  void move(double dx, double dy) override;
  void scale(double factor) override;

private:
  point_t center_;
  double side_;
};

}

#endif
