#include "rectangle.h"
#include <stdexcept>

namespace nepochatova {

  Rectangle::Rectangle() : pos_(0.0, 0.0), width_(1.0), height_(1.0) {}

  Rectangle::Rectangle(const point_t& pos, double width, double height) : pos_(pos), width_(width), height_(height)
  {
    if (width_ <= 0.0 || height_ <= 0.0) {
      throw std::invalid_argument("Width and height must be positive");
    }
  }

  double Rectangle::getArea() const {
    return width_ * height_;
  }

  rectangle_t Rectangle::getFrameRect() const {
    return rectangle_t{width_, height_, pos_};
  }

  void Rectangle::move(point_t newPos) {
    pos_ = newPos;
  }

  void Rectangle::move(double dx, double dy) {
    pos_.x += dx;
    pos_.y += dy;
  }

  void Rectangle::scale(double k) {
    if (k <= 0.0) {
      throw std::invalid_argument("Coefficient must be positive");
    }
    width_ *= k;
    height_ *= k;
  }
}
