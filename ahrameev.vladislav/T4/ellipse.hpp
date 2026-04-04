#ifndef ELLIPSE_HPP
#define ELLIPSE_HPP
#include "shape.hpp"

namespace akhrameev {
class Ellipse : public Shape {
public:
    Ellipse(double rx, double ry, point_t center);
    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void move(point_t to) override;
    void move(double dx, double dy) override;
    void scale(double factor) override;
private:
    double rx_; double ry_; point_t center_;
};
} 
#endif 