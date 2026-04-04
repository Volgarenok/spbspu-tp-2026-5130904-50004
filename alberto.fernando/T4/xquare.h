#ifndef XQUARE_HPP
#define XQUARE_HPP

#include "shape.hpp"

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
