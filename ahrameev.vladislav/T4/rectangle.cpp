#include "rectangle.hpp"

namespace akhrameev {
Rectangle::Rectangle(double w, double h, point_t c) : width_(w), height_(h), center_(c) {}
double Rectangle::getArea() const { return width_ * height_; }
rectangle_t Rectangle::getFrameRect() const { return {width_, height_, center_}; }
void Rectangle::move(point_t to) { center_ = to; }
void Rectangle::move(double dx, double dy) { center_.x += dx; center_.y += dy; }
void Rectangle::scale(double f) { width_ *= f; height_ *= f; }
} 