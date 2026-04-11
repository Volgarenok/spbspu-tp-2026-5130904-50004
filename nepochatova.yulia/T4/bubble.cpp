#include "bubble.h"
#include <stdexcept>
#include <cmath>

namespace nepochatova {

  Bubble::Bubble(point_t pivot, point_t geom_center, double radius) : pivot_(pivot), geom_center_(geom_center), radius_(radius)
  {
    if (radius_ <= 0.0) {
      throw std::invalid_argument("Bubble: radius must be positive");
    }
    double dist = std::hypot(pivot_.x - geom_center_.x, pivot_.y - geom_center_.y);
    if (dist >= radius_) {
      throw std::invalid_argument("Bubble: pivot must be strictly inside the circle");
    }
    if (dist < 1e-9) {
      throw std::invalid_argument("Bubble: pivot cannot coincide with geometric center");
    }
  }

  double Bubble::getArea() const {
    return std::acos(-1.0) * radius_ * radius_;
  }

  rectangle_t Bubble::getFrameRect() const {
    return rectangle_t{2.0 * radius_, 2.0 * radius_, geom_center_};
  }

  void Bubble::move(point_t newPos) {
    double dx = newPos.x - pivot_.x;
    double dy = newPos.y - pivot_.y;
    pivot_ = newPos;
    geom_center_.x += dx;
    geom_center_.y += dy;
  }

  void Bubble::move(double dx, double dy) {
    pivot_.x += dx;
    pivot_.y += dy;
    geom_center_.x += dx;
    geom_center_.y += dy;
  }

  void Bubble::scale(double k) {
    if (k <= 0.0) {
      throw std::invalid_argument("Bubble: scale coefficient must be positive");
    }
    radius_ *= k;
    geom_center_.x = pivot_.x + (geom_center_.x - pivot_.x) * k;
    geom_center_.y = pivot_.y + (geom_center_.y - pivot_.y) * k;
  }
}