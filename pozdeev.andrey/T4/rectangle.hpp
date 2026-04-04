#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

#include "shape.hpp"

namespace pozdeev {

class Rectangle : public Shape
{
public:
  Rectangle(double width, double height, const point_t& pos);

  double getArea() const override;
  rectangle_t getFrameRect() const override;
  void move(double dx, double dy) override;
  void move(const point_t& point) override;
  void scale(double coefficient) override;

private:
  rectangle_t rect_;
};

}

#endif
