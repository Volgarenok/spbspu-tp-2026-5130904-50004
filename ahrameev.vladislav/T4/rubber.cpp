#include "rubber.hpp"
#include <cmath>
#include <algorithm>

namespace akhrameev {
constexpr double PI = 3.14159265358979323846;

Rubber::Rubber(point_t sc, double rs, point_t lc, double rl)
    : small_center_(sc), r_small_(rs), large_center_(lc), r_large_(rl) {}

double Rubber::getArea() const { return PI * (r_large_ * r_large_ - r_small_ * r_small_); }

rectangle_t Rubber::getFrameRect() const {
    double min_x = std::min(small_center_.x - r_small_, large_center_.x - r_large_);
    double max_x = std::max(small_center_.x + r_small_, large_center_.x + r_large_);
    double min_y = std::min(small_center_.y - r_small_, large_center_.y - r_large_);
    double max_y = std::max(small_center_.y + r_small_, large_center_.y + r_large_);
    return {max_x - min_x, max_y - min_y, {(min_x + max_x) / 2.0, (min_y + max_y) / 2.0}};
}

void Rubber::move(point_t to) {
    double dx = to.x - small_center_.x; double dy = to.y - small_center_.y; move(dx, dy);
}
void Rubber::move(double dx, double dy) {
    small_center_.x += dx; small_center_.y += dy;
    large_center_.x += dx; large_center_.y += dy;
}
void Rubber::scale(double factor) {
    r_small_ *= factor; r_large_ *= factor;
    large_center_.x = small_center_.x + (large_center_.x - small_center_.x) * factor;
    large_center_.y = small_center_.y + (large_center_.y - small_center_.y) * factor;
}
} 