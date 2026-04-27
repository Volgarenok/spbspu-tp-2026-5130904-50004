#include "triangle.hpp"
#include <cmath>
#include <stdexcept>

namespace
{
  double getSignedArea(
    const aydogan::point_t& first,
    const aydogan::point_t& second,
    const aydogan::point_t& third
  )
  {
    return (
      first.x_ * (second.y_ - third.y_) +
      second.x_ * (third.y_ - first.y_) +
      third.x_ * (first.y_ - second.y_)
    ) / 2.0;
  }

  aydogan::point_t getCenter(
    const aydogan::point_t& first,
    const aydogan::point_t& second,
    const aydogan::point_t& third
  )
  {
    return aydogan::point_t(
      (first.x_ + second.x_ + third.x_) / 3.0,
      (first.y_ + second.y_ + third.y_) / 3.0
    );
  }
}

aydogan::Triangle::Triangle(
  const point_t& first,
  const point_t& second,
  const point_t& third
):
  first_(first),
  second_(second),
  third_(third),
  center_(getCenter(first, second, third))
{
  if (std::abs(getSignedArea(first_, second_, third_)) < 0.000001)
  {
    throw std::invalid_argument("Invalid triangle points");
  }
}
