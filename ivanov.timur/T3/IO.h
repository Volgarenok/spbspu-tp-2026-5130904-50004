#ifndef IO_H
#define IO_H
#include "Polygon.h"
#include <ios>
#include <istream>

using namespace ivanov;
namespace ivanov {

struct DelimiterIO {
  char exp;
};

struct PointIO {
  Point& ref;
};

class IOGuard {
public:
  explicit IOGuard(std::basic_ios<char>& s)
      : s_(s), width_(s.width()), prc_(s.precision()),
        fmt_(s.flags()), fill_(s.fill()) {}

  ~IOGuard() {
    s_.width(width_);
    s_.fill(fill_);
    s_.precision(prc_);
    s_.flags(fmt_);
  }

private:
  std::basic_ios<char>& s_;
  std::streamsize width_;
  std::streamsize prc_;
  std::basic_ios<char>::fmtflags fmt_;
  char fill_;
};

inline std::istream& operator>>(std::istream& in, DelimiterIO&& dest) {
  std::istream::sentry sentry(in);
  if (!sentry) return in;
  char c = 0;
  in >> c;
  if (in && c != dest.exp) in.setstate(std::ios::failbit);
  return in;
}

inline std::istream& operator>>(std::istream& in, PointIO&& dest) {
  std::istream::sentry sentry(in);
  if (!sentry) return in;

  Point temp;
  in >> DelimiterIO{'('} >> temp.x >> DelimiterIO{';'} >> temp.y >> DelimiterIO{')'};
  if (in) {
    dest.ref = temp;
  }
  return in;
}

inline std::istream& operator>>(std::istream& in, Polygon& dest) {
  std::istream::sentry sentry(in);
  if (!sentry) return in;

  int n = 0;
  if (!(in >> n) || n <= 0) {
    in.setstate(std::ios::failbit);
    return in;
  }

  std::vector<Point> points;
  points.reserve(n);
  for (int i = 0; i < n; ++i) {
    Point p;
    PointIO pio{p};
    if (!(in >> std::move(pio))) {
      return in;
    }
    points.push_back(p);
  }

  dest.pts = std::move(points);
  return in;
}

}

#endif
