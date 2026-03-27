#include "Shape.h"

alekseev::Rectangle::Rectangle(double width, double height, point_t pos):
  rect_(rectangle_t{width, height, pos})
{
}

double alekseev::Rectangle::getArea() const
{
  return rect_.height_ * rect_.width_;
}

alekseev::rectangle_t alekseev::Rectangle::getFrameRect() const
{
  return rect_;
}

void alekseev::Rectangle::move(point_t new_center)
{
  rect_.pos_ = new_center;
}

void alekseev::Rectangle::move(double x, double y)
{
  rect_.pos_.x_ += x;
  rect_.pos_.y_ += y;
}

void alekseev::Rectangle::scale(double k)
{
  rect_.width_ *= k;
  rect_.height_ *= k;
}

alekseev::Circle::Circle(double radius, point_t center):
  radius_(radius),
  center_(center)
{
}

double alekseev::Circle::getArea() const
{
  return PI * radius_ * radius_;
}

alekseev::rectangle_t alekseev::Circle::getFrameRect() const
{
  return rectangle_t{2 * radius_, 2 * radius_, center_};
}

void alekseev::Circle::move(point_t new_center)
{
  center_ = new_center;
}

void alekseev::Circle::move(double x, double y)
{
  center_.x_ += x;
  center_.y_ += y;
}

void alekseev::Circle::scale(double k)
{
  radius_ *= k;
}
