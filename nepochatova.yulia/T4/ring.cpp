#include "ring.h"
#include <stdexcept>
#include <cmath>

namespace nepochatova {

  Ring::Ring(point_t center, double r_outer, double r_inner) : center_(center), r_outer_(r_outer), r_inner_(r_inner)
  {
    if (r_outer_ <= 0.0 || r_inner_ <= 0.0) {
      throw std::invalid_argument("Ring: radii must be positive");
    }
    if (r_inner_ >= r_outer_) {
      throw std::invalid_argument("Ring: inner radius must be smaller than outer radius");
    }
  }

  double Ring::getArea() const {
    double pi = std::acos(-1.0);
    return pi * (r_outer_ * r_outer_ - r_inner_ * r_inner_);
  }

  rectangle_t Ring::getFrameRect() const {
    return rectangle_t{2.0 * r_outer_, 2.0 * r_outer_, center_};
  }

  void Ring::move(point_t newPos) {
    center_ = newPos;
  }

  void Ring::move(double dx, double dy) {
    center_.x += dx;
    center_.y += dy;
  }

  void Ring::scale(double k) {
    if (k <= 0.0) {
      throw std::invalid_argument("Ring: scale coefficient must be positive");
    }
    r_outer_ *= k;
    r_inner_ *= k;
  }
}
