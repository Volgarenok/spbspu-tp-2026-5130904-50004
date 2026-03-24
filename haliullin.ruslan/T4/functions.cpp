#include "functions.hpp"
#include <iostream>
#include <iomanip>
#include <limits>
#include <cmath>

namespace haliullin
{
  point_t getRightBottomFrame(const rectangle_t & frame)
  {
    double halfWidth = frame.width / 2.0;
    double halfHeight = frame.height / 2.0;
    return point_t(frame.pos.x + halfWidth, frame.pos.y + halfHeight);
  }

  void displayFigure(const std::weak_ptr< Shape > & figure, const std::string & name, size_t id)
  {
    auto shape = figure.lock();
    if (!shape)
    {
      throw std::runtime_error("Expired weak pointer");
    }
    rectangle_t frame = shape->getFrameRect();
    std::cout << id << ". " << name << "\n";
    std::cout << "area = " << shape->getArea() << "\n";
    std::cout << "frame: center(" << frame.pos.x << ";" << frame.pos.y << "), width = "
    << frame.width << ", height = " << frame.height << "\n";
  }

  void displayAllFigures(const std::vector< std::weak_ptr< Shape > > & figures, const std::vector< std::string > & names)
  {
    double total = 0.0;
    std::cout << std::fixed << std::setprecision(2);
    for (size_t i = 0; i < figures.size(); ++i)
    {
      auto shape = figures[i].lock();
      if (shape)
      {
        displayFigure(figures[i], names[i], i + 1);
        total += shape->getArea();
      }
    }
    std::cout << "Total area = " << total << "\n";
  }

  rectangle_t getTotalFrame(const std::vector< std::weak_ptr< Shape > > & figures)
  {
    if (figures.empty())
    {
      return rectangle_t(0.0, 0.0, point_t(0.0, 0.0));
    }
    double minX = std::numeric_limits< double >::max();
    double minY = std::numeric_limits< double >::max();
    double maxX = std::numeric_limits< double >::lowest();
    double maxY = std::numeric_limits< double >::lowest();
    for (const auto & wptr : figures)
    {
      auto shape = wptr.lock();
      if (!shape)
      {
        continue;
      }
      rectangle_t frame = shape->getFrameRect();
      double halfWidth = frame.width / 2.0;
      double halfHeight = frame.height / 2.0;
      double left = frame.pos.x - halfWidth;
      double right = frame.pos.x + halfWidth;
      double bottom = frame.pos.y - halfHeight;
      double top = frame.pos.y + halfHeight;
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
    double width = maxX - minX;
    double height = maxY - minY;
    point_t center = {(minX + maxX) / 2.0, (minY + maxY) / 2.0};
    return rectangle_t(width, height, center);
  }

  void displayTotalFrame(const rectangle_t & frame)
  {
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "Total frame: center(" << frame.pos.x << ";" << frame.pos.y << ")\n";
    std::cout << "width = " << frame.width << ", height = " << frame.height << "\n";
  }

}
