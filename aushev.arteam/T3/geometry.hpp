#ifndef AUSHEV_GEOMETRY_HPP
#define AUSHEV_GEOMETRY_HPP

#include <vector>
#include <cmath>
#include <algorithm>

namespace aushev {

struct Point {
    int x_;
    int y_;

    bool operator==(const Point& other) const {
        return x_ == other.x_ && y_ == other.y_;
    }

    bool operator<(const Point& other) const {
        if (x_ != other.x_) {
            return x_ < other.x_;
        }
        return y_ < other.y_;
    }
};

struct Polygon {
    std::vector<Point> points_;

    double getArea() const {
        double area = 0.0;
        size_t n = points_.size();
        for (size_t i = 0; i < n; ++i) {
            size_t j = (i + 1) % n;
            area += points_[i].x_ * points_[j].y_ - points_[j].x_ * points_[i].y_;
        }
        return std::abs(area) / 2.0;
    }
};

}

#endif
