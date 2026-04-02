#ifndef CIRCLE_H
#define CIRCLE_H
#include <cmath>
#include <stdexcept>
#include "Shape.h"
#include "POD.h"

class Circle : public Shape{
private:
  point_t centre;
  double radius;

public:
  Circle(const double& x, const double& y, const double& r):
    centre(point_t(x, y)), radius(r) {}
  virtual ~Circle() = default;

  double getArea() override {
    return M_PI*radius*radius;
  }
  rectangle_t getFrameRect() override {
    return rectangle_t(2*radius, 2*radius, point_t(centre.x - radius, centre.y - radius));
  }

  void move(const double& delta_x, const double& delta_y) override {
    centre.x += delta_x;
    centre.y += delta_y;
  }
  void move(const point_t& new_point) override {
    move(new_point.x - centre.x, new_point.y - centre.y);
  }

  void scale(const point_t& p, const double& k) override {
    if (k <= 0) throw std::logic_error("Cannot scale by negative");
    move(p);
    radius *= k;
  }
};

#endif
