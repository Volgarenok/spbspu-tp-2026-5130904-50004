#ifndef SHAPE_HPP
#define SHAPE_HPP

namespace akhrameev {

struct point_t {
    double x = 0.0;
    double y = 0.0;
};

struct rectangle_t {
    double width = 0.0;
    double height = 0.0;
    point_t pos{0.0, 0.0};
};

class Shape {
public:
    virtual ~Shape() = default;
    virtual double getArea() const = 0;
    virtual rectangle_t getFrameRect() const = 0;
    virtual void move(point_t to) = 0;
    virtual void move(double dx, double dy) = 0;
    virtual void scale(double factor) = 0;
};

} 

#endif 