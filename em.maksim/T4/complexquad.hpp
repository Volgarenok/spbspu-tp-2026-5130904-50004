#ifndef EM_COMPLEXQUAD_HPP
#define EM_COMPLEXQUAD_HPP

#include "shape.hpp"

#include <array>

namespace em {

class Complexquad : public Shape
{
public:
  explicit Complexquad(std::array<point_t, 4> vertices);

  double getArea() const override;
  rectangle_t getFrameRect() const override;
  void move(point_t dest) override;
  void move(double dx, double dy) override;
  void scale(double factor) override;

private:
  point_t center_;
  std::array<point_t, 4> vertices_;

  static point_t findIntersection(point_t p1, point_t p2, point_t p3, point_t p4);
  void recalcCenter();
};

}

#endif
