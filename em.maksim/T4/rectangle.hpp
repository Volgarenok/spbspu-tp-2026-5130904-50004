#ifndef EM_RECTANGLE_HPP
#define EM_RECTANGLE_HPP

#include "shape.hpp"

namespace em {

class Rectangle : public Shape
{
public:
  Rectangle(point_t center, double width, double height);

  double getArea() const override;
  rectangle_t getFrameRect() const override;
  void move(point_t dest) override;
  void move(double dx, double dy) override;
  void scale(double factor) override;

private:
  point_t center_;
  double width_;
  double height_;
};

}

#endif
