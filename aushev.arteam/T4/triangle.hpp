#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP

#include "shape.hpp"

namespace aushev
{
  class Triangle : public Shape
  {
  public:
    Triangle(point_t a, point_t b, point_t c);
    ~Triangle() override = default;

    double getArea() const override;
    rectangle_t getFrameRect() const override;

    void move(const point_t& p) override;
    void move(double dx, double dy) override;
    void scale(double k) override;

  private:
    point_t a_;
    point_t b_;
    point_t c_;

    point_t getCentroid() const;
  };
}

#endif
