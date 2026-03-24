#ifndef DIAMOND_HPP
#define DIAMOND_HPP

#include "shape.hpp"

namespace haliullin
{
  class Diamond : public Shape
  {
  public:
    Diamond(double d1, double d2, const point_t & p);
    ~Diamond() override = default;

    double getArea() const override;
    rectangle_t getFrameRect() const override;

    void move(const point_t & pt) override;
    void move(double dx, double dy) override;

    void scale(double k) override;

  private:
    double gor_d;
    double vert_d;
    point_t pos;
  };
}

#endif
