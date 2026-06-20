#include "functions.hpp"
#include "rectangle_shape.hpp"
#include "xquare.hpp"
#include "complexquad.hpp"
#include <iostream>
#include <limits>
#include <memory>

namespace velizade
{

  rectangle_t getCommonFrameRect(const std::vector<std::shared_ptr<Shape>>& shapes)
  {
    if (shapes.empty())
    {
      return {{0, 0}, 0, 0};
    }

    double minX = std::numeric_limits<double>::max();
    double maxX = -std::numeric_limits<double>::max();
    double minY = std::numeric_limits<double>::max();
    double maxY = -std::numeric_limits<double>::max();

    for (const auto& ptr : shapes)
    {
      auto rect = ptr->getFrameRect();
      double left   = rect.pos.x - rect.width / 2;
      double right  = rect.pos.x + rect.width / 2;
      double bottom = rect.pos.y - rect.height / 2;
      double top    = rect.pos.y + rect.height / 2;

      if (left < minX)
      {
        minX = left;
      }
      if (right > maxX)
      {
        maxX = right;
      }
      if (bottom < minY)
      {
        minY = bottom;
      }
      if (top > maxY)
      {
        maxY = top;
      }
    }

    double width  = maxX - minX;
    double height = maxY - minY;
    point_t center{(minX + maxX) / 2, (minY + maxY) / 2};
    return {center, width, height};
  }

  void printShapeInfo(const std::weak_ptr<Shape>& wptr)
  {
    auto sptr = wptr.lock();
    if (!sptr)
    {
      std::cerr << "Shape no longer exists\n";
      return;
    }
    auto rect = sptr->getFrameRect();
    std::cout << "  Area: " << sptr->getArea() << ", FrameRect: center=(" << rect.pos.x << ", " << rect.pos.y << "), w=" << rect.width
              << ", h=" << rect.height << "\n";
  }

  void printAllInfo(const std::vector<std::shared_ptr<Shape>>& shapes)
  {
    double totalArea = 0.0;
    for (const auto& ptr : shapes)
    {
      totalArea += ptr->getArea();
      printShapeInfo(std::weak_ptr<Shape>(ptr));
    }
    std::cout << "Total area: " << totalArea << "\n";

    auto common = getCommonFrameRect(shapes);
    std::cout << "Common FrameRect: center=(" << common.pos.x << ", " << common.pos.y << "), w=" << common.width << ", h=" << common.height << "\n";
  }

  void scaleShapes(std::vector<std::shared_ptr<Shape>>& shapes, const point_t& pivot, double k)
  {
    if (k <= 0)
    {
      throw std::invalid_argument("Scale factor must be positive");
    }

    for (auto& ptr : shapes)
    {
      point_t center;
      if (auto rect = std::dynamic_pointer_cast<Rectangle>(ptr))
      {
        center = rect->getCenter();
      }
      else if (auto xs = std::dynamic_pointer_cast<Xsquare>(ptr))
      {
        center = xs->getCenter();
      }
      else if (auto cq = std::dynamic_pointer_cast<Complexquad>(ptr))
      {
        center = cq->getCenter();
      }
      else
      {
        center = ptr->getFrameRect().pos;
      }

      ptr->move(pivot);
      ptr->scale(k);
      point_t newCenter{pivot.x + k * (center.x - pivot.x), pivot.y + k * (center.y - pivot.y)};
      ptr->move(newCenter);
    }
  }

}
