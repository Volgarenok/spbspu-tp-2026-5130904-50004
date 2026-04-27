#ifndef SQUARE_HPP
#define SQUARE_HPP

#include "shape.hpp"

namespace aydogan
{
  class Square: public Shape
  {
  public:
    Square(double side, const point_t& center);

    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void move(const point_t& point) override;
    void move(double dx, double dy) override;
    void scale(double coefficient) override;

  private:
    double side_;
    point_t center_;
  };
}

#endif
