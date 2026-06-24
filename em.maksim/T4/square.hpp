#ifndef EM_SQUARE_HPP
#define EM_SQUARE_HPP

#include "shape.hpp"

namespace em {

class Square : public Shape
{
public:
  Square(point_t center, double side);

  double getArea() const override;
  rectangle_t getFrameRect() const override;
  void move(point_t dest) override;
  void move(double dx, double dy) override;
  void scale(double factor) override;

private:
  point_t center_;
  double side_;
};

}

#endif
