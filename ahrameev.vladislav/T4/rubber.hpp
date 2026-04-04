#ifndef RUBBER_HPP
#define RUBBER_HPP
#include "shape.hpp"

namespace akhrameev {
class Rubber : public Shape {
public:
    Rubber(point_t small_center, double r_small, point_t large_center, double r_large);
    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void move(point_t to) override;
    void move(double dx, double dy) override;
    void scale(double factor) override;
private:
    point_t small_center_, large_center_;
    double r_small_, r_large_;
};
} 
#endif 