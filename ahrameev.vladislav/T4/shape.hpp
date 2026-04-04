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

} 

#endif 