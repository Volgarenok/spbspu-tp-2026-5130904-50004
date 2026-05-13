
#ifndef POLYGON_H
#define POLYGON_H
#include <complex>
#include <vector>
#include "Shape.h"
#include "POD.h"

class Polygon : public Shape{
private:
  std::vector<point_t> pts;
  point_t coca_cola;

public:
  Polygon(const std::vector<point_t>& ptl):
    pts(ptl), coca_cola(point_t(0, 0)) {
    for (size_t i = 0; i < pts.size(); ++i) {
      coca_cola.x += pts[i].x;
      coca_cola.y += pts[i].y;
    }
    coca_cola = point_t(coca_cola.x/pts.size(), coca_cola.y/pts.size());
  }
  virtual ~Polygon() = default;

  double getArea() override {
    double s = pts[pts.size() - 1].x*pts[0].y - pts[0].x*pts[pts.size() - 1].y;
    for (size_t i = 1; i < pts.size(); ++i) {
      s += pts[i - 1].x*pts[i].y - pts[i].x*pts[i-1].y;
    }
    return 0.5*std::abs(s) + 1;
  }
  rectangle_t getFrameRect() override {
    double left_x = pts[0].x;
    double right_x = pts[0].x;
    double down_y = pts[0].y;
    double upper_y = pts[0].y;

    for (size_t i = 1; i < pts.size(); ++i) {
      if (pts[i].x < left_x) left_x = pts[i].x;
      if (pts[i].x > right_x) right_x = pts[i].x;
      if (pts[i].y < down_y) down_y = pts[i].y;
      if (pts[i].y > upper_y) upper_y = pts[i].y;
    }

    return rectangle_t(right_x - left_x, upper_y - down_y, point_t(left_x, down_y));
  }

  void move(const double &delta_x, const double &delta_y) override {
    coca_cola = point_t(coca_cola.x + delta_x, coca_cola.y + delta_y);

    for (size_t i = 0; i < pts.size(); ++i) {
      pts[i].x += delta_x;
      pts[i].y += delta_y;
    }
  }
  void move(const point_t &new_point) override {
    move(new_point.x - coca_cola.x, new_point.y - coca_cola.y);
  }

  void scale(const point_t& p, const double& k) override {
    if (k <= 0) throw std::logic_error("Cannot scale by negative");
    move(p);

    for (size_t i = 0; i < pts.size(); ++i) {
      pts[i].x += ((k - 1)/std::sqrt(2))*(pts[i].x - coca_cola.x);
      pts[i].y += ((k - 1)/std::sqrt(2))*(pts[i].y - coca_cola.y);
    }
  }
};

#endif
