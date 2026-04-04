#ifndef VASILENKO_COMPLEXQUAD_HPP
#define VASILENKO_COMPLEXQUAD_HPP

#include "shape.hpp"

namespace vasilenko {
  class Complexquad : public Shape {
  public:
    Complexquad(const point_t &a, const point_t &b, const point_t &c, const point_t &d);
    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void move(const point_t &point) override;
    void move(double dx, double dy) override;
    void scale(double coefficient) override;

  private:
    point_t a_;
    point_t b_;
    point_t c_;
    point_t d_;

    point_t getCenter() const;
    bool segmentsIntersect(const point_t &p1, const point_t &p2, const point_t &p3, const point_t &p4) const;
    point_t getIntersection(const point_t &p1, const point_t &p2, const point_t &p3, const point_t &p4) const;
    double getTriangleArea(const point_t &p1, const point_t &p2, const point_t &p3) const;
  };
}

#endif
