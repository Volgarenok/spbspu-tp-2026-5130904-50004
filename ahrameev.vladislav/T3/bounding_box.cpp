#include "bounding_box.hpp"

namespace ahrameev
{

  bool lessByX(const Point& a, const Point& b)
  {
    return a.x < b.x;
  }

  bool lessByY(const Point& a, const Point& b)
  {
    return a.y < b.y;
  }

}