#ifndef DIAMOND_HPP
#define DIAMOND_HPP

#include "shape.hpp"

namespace pozdeev {

class Diamond : public Shape
{
public:
  Diamond(double diagonalX, double diagonalY, const point_t& center);

  double getArea() const override;
  rectangle_t getFrameRect() const override;
  void move(double dx, double dy) override;
  void move(const point_t& point) override;
  void scale(double coefficient) override;

private:
  double diagX_;
  double diagY_;
  point_t center_;
};

}

#endif
