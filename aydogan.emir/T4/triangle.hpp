#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP

#include "shape.hpp"

namespace aydogan
{
  class Triangle: public Shape
  {
  public:
    Triangle(const point_t& first, const point_t& second, const point_t& third);

    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void move(const point_t& point) override;
    void move(double dx, double dy) override;
    void scale(double coefficient) override;

  private:
    point_t first_;
    point_t second_;
    point_t third_;
    point_t center_;
  };
}

#endif
