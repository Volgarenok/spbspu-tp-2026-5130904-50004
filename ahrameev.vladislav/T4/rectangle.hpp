#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP
#include "shape.hpp"

namespace akhrameev {
class Rectangle : public Shape {
public:
  Rectangle(double width, double height, point_t center);
  double getArea() const override;
  rectangle_t getFrameRect() const override;
  void move(point_t to) override;
  void move(double dx, double dy) override;
  void scale(double factor) override;
private:
  double width_; double height_; point_t center_;
};
} 
#endif 