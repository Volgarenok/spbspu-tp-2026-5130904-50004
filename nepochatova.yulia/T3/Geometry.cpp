#include "Geometry.h"
#include "IOGuard.h"
#include <limits>
#include <algorithm>

namespace nepochatova {
  struct SemiDelim {
    char c;
  };

  std::istream& operator>>(std::istream& in, SemiDelim&& d) {
    std::istream::sentry s(in);
    if (!s) return in;
    char ch;
    if (!(in >> ch) || ch != d.c)
      in.setstate(std::ios_base::failbit);
    return in;
  }
}