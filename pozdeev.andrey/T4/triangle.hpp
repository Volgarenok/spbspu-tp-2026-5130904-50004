#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP

#include "shape.hpp"

namespace pozdeev {

class Triangle : public Shape
{
public:
  Triangle(double base, double height, const point_t& centroid);

  double getArea() const override;
  rectangle_t getFrameRect() const override;
  void move(double dx, double dy) override;
  void move(const point_t& point) override;
  void scale(double coefficient) override;

private:
  double base_;
  double height_;
  point_t centroid_;
};

}

#endif
