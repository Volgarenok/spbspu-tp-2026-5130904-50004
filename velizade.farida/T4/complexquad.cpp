#include "complexquad.hpp"
#include <stdexcept>
#include <algorithm>
#include <cmath>

namespace velizade
{

  point_t Complexquad::intersection(const point_t& a1, const point_t& b1, const point_t& a2, const point_t& b2)
  {
    double denom = (b1.x - a1.x) * (b2.y - a2.y) - (b1.y - a1.y) * (b2.x - a2.x);
    if (std::fabs(denom) < 1e-12)
    {
      throw std::runtime_error("Diagonals are parallel, no intersection");
    }
    double t = ((a2.x - a1.x) * (b2.y - a2.y) - (a2.y - a1.y) * (b2.x - a2.x)) / denom;
    return {a1.x + t * (b1.x - a1.x), a1.y + t * (b1.y - a1.y)};
  }

  Complexquad::Complexquad(const std::array<point_t, 4>& vertices):
        vertices_(vertices)
  {
    center_ = intersection(vertices[0], vertices[2], vertices[1], vertices[3]);
  }

  point_t Complexquad::getCenter() const
  {
    return center_;
  }

  double Complexquad::getArea() const
  {
    double area = 0.0;
    for (size_t i = 0; i < 4; ++i)
    {
      size_t j = (i + 1) % 4;
      area += vertices_[i].x * vertices_[j].y;
      area -= vertices_[j].x * vertices_[i].y;
    }
    return std::fabs(area) / 2.0;
  }

  rectangle_t Complexquad::getFrameRect() const
  {
    double minX = vertices_[0].x;
    double maxX = vertices_[0].x;
    double minY = vertices_[0].y;
    double maxY = vertices_[0].y;
    for (size_t i = 1; i < 4; ++i)
    {
      minX = std::min(minX, vertices_[i].x);
      maxX = std::max(maxX, vertices_[i].x);
      minY = std::min(minY, vertices_[i].y);
      maxY = std::max(maxY, vertices_[i].y);
    }
    point_t center{(minX + maxX) / 2, (minY + maxY) / 2};
    return {center, maxX - minX, maxY - minY};
  }

  void Complexquad::move(const point_t& newPos)
  {
    double dx = newPos.x - center_.x;
    double dy = newPos.y - center_.y;
    for (auto& v : vertices_)
    {
      v.x += dx;
      v.y += dy;
    }
    center_ = newPos;
  }

  void Complexquad::move(double dx, double dy)
  {
    for (auto& v : vertices_)
    {
      v.x += dx;
      v.y += dy;
    }
    center_.x += dx;
    center_.y += dy;
  }

  void Complexquad::scale(double k)
  {
    if (k <= 0)
    {
      throw std::invalid_argument("Scale factor must be positive");
    }
    for (auto& v : vertices_)
    {
      v.x = center_.x + k * (v.x - center_.x);
      v.y = center_.y + k * (v.y - center_.y);
    }
  }

}
