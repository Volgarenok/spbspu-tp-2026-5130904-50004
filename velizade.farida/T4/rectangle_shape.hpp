#ifndef RECTANGLE_SHAPE_HPP
#define RECTANGLE_SHAPE_HPP

#include "shape.hpp"

namespace velizade
{
  class Rectangle : public Shape
  {
  public:
    Rectangle(const point_t& center, double width, double height);

    point_t getCenter() const;

    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void move(const point_t& newPos) override;
    void move(double dx, double dy) override;
    void scale(double k) override;

  private:
    point_t center_;
    double width_;
    double height_;
  };
}

#endif
