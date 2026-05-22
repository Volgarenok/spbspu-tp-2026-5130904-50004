#include "polygon.hpp"
#include <cmath>

double zinoviev::Polygon::getArea() const
{
  double area = 0.0;

  size_t i = 0;
  for (; i < vertices_.size() - 1; ++i)
  {
    area += (vertices_[i].x * vertices_[i + 1].y);
    area -= (vertices_[i + 1].x * vertices_[i].y);
  }

  area += (vertices_[i].x * vertices_[0].y);
  area -= (vertices_[0].x * vertices_[i].y);

  area = std::abs(0.5 * area);

  return area;
}

zinoviev::rectangle_t zinoviev::Polygon::getFrameRect() const
{
  double x_min = vertices_[0].x, x_max = vertices_[0].x;
  double y_min = vertices_[0].y, y_max = vertices_[0].y;

  for (size_t i = 1; i < vertices_.size(); ++i)
  {
    if (vertices_[i].x < x_min)
      x_min = vertices_[i].x;
    else if (vertices_[i].x > x_max)
      x_max = vertices_[i].x;

    if (vertices_[i].y < y_min)
      y_min = vertices_[i].y;
    else if (vertices_[i].y > y_max)
      y_max = vertices_[i].y;
  }

  point_t pos_r{ 0.5 * (x_max + x_min), 0.5 * (y_max + y_min) };

  return rectangle_t{pos_r, x_max - x_min, y_max - y_min};
}

void zinoviev::Polygon::move(const point_t& newPos)
{
  double dx = newPos.x - centroid_.x;
  double dy = newPos.y - centroid_.y;

  move(dx, dy);
}

void zinoviev::Polygon::move(double dx, double dy)
{
  for (size_t i = 0; i < vertices_.size(); ++i)
  {
    vertices_[i].x += dx;
    vertices_[i].y += dy;
  }

  centroid_.x += dx;
  centroid_.y += dy;
}

void zinoviev::Polygon::scale(double k)
{
  if (k <= 0.0)
    throw std::logic_error("Coefficient must be positive");

  for (size_t i = 0; i < vertices_.size(); ++i)
  {
    double dx = vertices_[i].x - centroid_.x;
    double dy = vertices_[i].y - centroid_.y;

    vertices_[i].x = centroid_.x + k * dx;
    vertices_[i].y = centroid_.y + k * dy;
  }
}
