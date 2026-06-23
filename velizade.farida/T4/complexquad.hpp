#ifndef COMPLEXQUAD_HPP
#define COMPLEXQUAD_HPP

#include "shape.hpp"
#include <array>

namespace velizade
{
  class Complexquad : public Shape
  {
  public:
    Complexquad(const std::array<point_t, 4>& vertices);

    point_t getCenter() const;

    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void move(const point_t& newPos) override;
    void move(double dx, double dy) override;
    void scale(double k) override;

  private:
    std::array<point_t, 4> vertices_;
    point_t center_;

    static point_t intersection(const point_t& a1, const point_t& b1, const point_t& a2, const point_t& b2);
  };
}

#endif
