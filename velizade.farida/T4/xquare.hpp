#ifndef XQUARE_HPP
#define XQUARE_HPP

#include "shape.hpp"

namespace velizade
{
  class Xsquare : public Shape
  {
  public:
    Xsquare(const point_t& center, double halfDiag);

    point_t getCenter() const;

    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void move(const point_t& newPos) override;
    void move(double dx, double dy) override;
    void scale(double k) override;

  private:
    point_t center_;
    double halfDiag_;
  };
}

#endif
