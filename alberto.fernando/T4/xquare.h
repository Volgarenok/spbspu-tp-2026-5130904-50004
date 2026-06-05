#ifndef XQUARE_H
#define XQUARE_H
#include "shape.h"

namespace alberto {

class Xquare : public Shape {
public:

  Xquare(const point_t& center, double halfDiag);

  double getArea() const override;
  rectangle_t getFrameRect() const override;
  void move(const point_t& dest) override;
  void move(double dx, double dy) override;
  void scale(double factor) override;

private:
  point_t center_;
  double halfDiag_;
};

}

#endif
