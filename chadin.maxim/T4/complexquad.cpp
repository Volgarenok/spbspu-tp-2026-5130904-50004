#include "complexquad.hpp"
#include <algorithm>
#include <cmath>
#include <stdexcept>

static bool getIntersection(const chadin::point_t& p1, const chadin::point_t& p2,
    const chadin::point_t& p3, const chadin::point_t& p4, chadin::point_t& out)
{
  const double den = (p1.x - p2.x) * (p3.y - p4.y) - (p1.y - p2.y) * (p3.x - p4.x);
  if (std::abs(den) < 1e-9) {
    return false;
  }
  const double t = ((p1.x - p3.x) * (p3.y - p4.y) - (p1.y - p3.y) * (p3.x - p4.x)) / den;
  const double u = ((p1.x - p3.x) * (p1.y - p2.y) - (p1.y - p3.y) * (p1.x - p2.x)) / den;
  if (t >= 0.0 && t <= 1.0 && u >= 0.0 && u <= 1.0) {
    out.x = p1.x + t * (p2.x - p1.x);
    out.y = p1.y + t * (p2.y - p1.y);
    return true;
  }
  return false;
}

namespace chadin {
  Complexquad::Complexquad(point_t a, point_t b, point_t c, point_t d):
    a_(a),
    b_(b),
    c_(c),
    d_(d)
  {
    point_t center;
    if (!getIntersection(a_, b_, c_, d_, center) && !getIntersection(b_, c_, d_, a_, center)) {
      throw std::invalid_argument("Vertices do not form a self-intersecting quadrilateral");
    }
  }
