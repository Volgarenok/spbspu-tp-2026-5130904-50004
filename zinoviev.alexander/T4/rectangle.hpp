#ifndef RECTANGLE_HPP

#define RECTANGLE_HPP
#include "shape.hpp"
#include <stdexcept>

namespace zinoviev
{
  class Rectangle : public Shape
  {
    point_t center_;
    double width_;
    double height_;

  public:

    Rectangle() :
      width_(1.0),
      height_(1.0)
    {}

    Rectangle(point_t pt, double width, double height) :
      center_(pt),
      width_(width),
      height_(height)
    {
      if (width_ <= 0.0 || height_ <= 0.0)
        throw std::invalid_argument("Width and Height must be positive");
    }

    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void move(const point_t& newPos) override;
    void move(double dx, double dy) override;
    void scale(double k) override;
  };
}
#endif
