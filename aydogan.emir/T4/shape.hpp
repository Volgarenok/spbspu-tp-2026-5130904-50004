#ifndef SHAPE_HPP
#define SHAPE_HPP

#include "base_types.hpp"
#include <memory>

namespace aydogan
{
  class Shape
  {
  public:
    virtual ~Shape() = default;

    virtual double getArea() const = 0;
    virtual rectangle_t getFrameRect() const = 0;
    virtual void move(const point_t& point) = 0;
    virtual void move(double dx, double dy) = 0;
    virtual void scale(double coefficient) = 0;
  };

  using ShapePtr = std::shared_ptr< Shape >;
  using WeakShape = std::weak_ptr< Shape >;
}

#endif
