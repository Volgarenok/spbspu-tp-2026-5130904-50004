#include "ellipse.hpp"
#include <cmath>

namespace akhrameev {
constexpr double PI = 3.14159265358979323846;
Ellipse::Ellipse(double rx, double ry, point_t c) : rx_(rx), ry_(ry), center_(c) {}
double Ellipse::getArea() const { return PI * rx_ * ry_; }
rectangle_t Ellipse::getFrameRect() const { return {rx_ * 2.0, ry_ * 2.0, center_}; }
void Ellipse::move(point_t to) { center_ = to; }
void Ellipse::move(double dx, double dy) { center_.x += dx; center_.y += dy; }
void Ellipse::scale(double f) { rx_ *= f; ry_ *= f; }
} 