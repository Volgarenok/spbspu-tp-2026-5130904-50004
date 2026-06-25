#include "Polygon.h"
#include <algorithm>
#include <iterator>

namespace chadin {
  namespace detail {

    struct read_point
    {
      std::istream& in;
      Point operator()() const
      {
        Point p;
        in >> p;
        return p;
      }
    };

  }
