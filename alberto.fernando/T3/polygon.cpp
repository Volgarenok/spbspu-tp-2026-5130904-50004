#include "polygon.hpp"

#include <algorithm>
#include <cmath>
#include <functional>
#include <iomanip>
#include <numeric>
#include <stdexcept>
#include <string>
#include <vector>

namespace alberto {

namespace detail {

struct ExpectChar
{
  char expected_ = '\0';
};

std::istream& operator>>(std::istream& in, ExpectChar ec)
{
  char c = '\0';
  if (in >> c && c != ec.expected_) {
    in.setstate(std::ios::failbit);
  }
  return in;
}

bool areaLess(const Polygon& a, const Polygon& b)
{
  return polygonArea(a) < polygonArea(b);
}

bool vertexLess(const Polygon& a, const Polygon& b)
{
  return a.points.size() < b.points.size();
}

bool isEven(const Polygon& p)
{
  return p.points.size() % 2 == 0;
}

bool isOdd(const Polygon& p)
{
  return p.points.size() % 2 != 0;
}

}

std::istream&
operator>>(std::istream& in, Point& p)
{
  using detail::ExpectChar;
  int x = 0;
  int y = 0;
  in >> ExpectChar{'('} >> x >> ExpectChar{';'} >> y >> ExpectChar{')'};
  if (in) {
    p = {x, y};
  }
  return in;
}

std::istream&
operator>>(std::istream& in, Polygon& poly)
{
  std::istream::sentry sentry(in);
  if (!sentry) {
    return in;
  }

  size_t count = 0;
  if (!(in >> count) || count < 3) {
    in.setstate(std::ios::failbit);
    return in;
  }

  std::vector< Point > pts(count);
  for (size_t i = 0; i < count; ++i) {
    if (!(in >> pts[i])) {
      return in;
    }
  }

  char c = '\0';
  while (in.get(c) && c != '\n') {
    if (c != ' ' && c != '\r') {
      in.setstate(std::ios::failbit);
      return in;
    }
  }

  poly.points = std::move(pts);
  return in;
}

std::ostream&
operator<<(std::ostream& out, const Point& p)
{
  out << "(" << p.x << ";" << p.y << ")";
  return out;
}

std::ostream&
operator<<(std::ostream& out, const Polygon& poly)
{
  out << poly.points.size();
  for (const auto& pt : poly.points) {
    out << " " << pt;
  }
  return out;
}

bool
operator==(const Point& a, const Point& b)
{
  return a.x == b.x && a.y == b.y;
}

bool
operator==(const Polygon& a, const Polygon& b)
{
  return a.points == b.points;
}

double
polygonArea(const Polygon& poly)
{
  const auto& pts = poly.points;
  const size_t n  = pts.size();

  const double twice = std::abs(
      std::accumulate(
          pts.begin(), pts.end(),
          0.0,
          [&pts, &n](double acc, const Point& pt) {
            const size_t i = static_cast< size_t >(&pt - pts.data());
            const size_t j = (i + 1) % n;
            return acc
                + static_cast< double >(pt.x) * pts[j].y
                - static_cast< double >(pts[j].x) * pt.y;
          }));
  return twice / 2.0;
}

void
cmdArea(std::ostream& out,
        const std::vector< Polygon >& polys,
        const std::string& arg)
{
  out << std::fixed << std::setprecision(1);

  if (arg == "EVEN") {
    out << std::accumulate(polys.begin(), polys.end(), 0.0,
        [](double acc, const Polygon& p) {
          return acc + (detail::isEven(p) ? polygonArea(p) : 0.0);
        }) << "\n";
  } else if (arg == "ODD") {
    out << std::accumulate(polys.begin(), polys.end(), 0.0,
        [](double acc, const Polygon& p) {
          return acc + (detail::isOdd(p) ? polygonArea(p) : 0.0);
        }) << "\n";
  } else if (arg == "MEAN") {
    if (polys.empty()) {
      throw std::invalid_argument("no polygons");
    }
    out << std::accumulate(polys.begin(), polys.end(), 0.0,
        [](double acc, const Polygon& p) {
          return acc + polygonArea(p);
        }) / polys.size() << "\n";
  } else {
    const size_t n = std::stoull(arg);
    if (n < 3) {
      throw std::invalid_argument("invalid vertex count");
    }
    out << std::accumulate(polys.begin(), polys.end(), 0.0,
        [n](double acc, const Polygon& p) {
          return acc + (p.points.size() == n ? polygonArea(p) : 0.0);
        }) << "\n";
  }
}

void
cmdMax(std::ostream& out,
       const std::vector< Polygon >& polys,
       const std::string& arg)
{
  if (polys.empty()) {
    throw std::invalid_argument("no polygons");
  }

  if (arg == "AREA") {
    out << std::fixed << std::setprecision(1)
        << polygonArea(*std::max_element(polys.begin(), polys.end(),
               detail::areaLess)) << "\n";
  } else if (arg == "VERTEXES") {
    out << std::max_element(polys.begin(), polys.end(),
            detail::vertexLess)->points.size() << "\n";
  } else {
    throw std::invalid_argument("invalid MAX argument");
  }
}

void
cmdMin(std::ostream& out,
       const std::vector< Polygon >& polys,
       const std::string& arg)
{
  if (polys.empty()) {
    throw std::invalid_argument("no polygons");
  }

  if (arg == "AREA") {
    out << std::fixed << std::setprecision(1)
        << polygonArea(*std::min_element(polys.begin(), polys.end(),
               detail::areaLess)) << "\n";
  } else if (arg == "VERTEXES") {
    out << std::min_element(polys.begin(), polys.end(),
            detail::vertexLess)->points.size() << "\n";
  } else {
    throw std::invalid_argument("invalid MIN argument");
  }
}

void
cmdCount(std::ostream& out,
         const std::vector< Polygon >& polys,
         const std::string& arg)
{
  if (arg == "EVEN") {
    out << std::count_if(polys.begin(), polys.end(), detail::isEven) << "\n";
  } else if (arg == "ODD") {
    out << std::count_if(polys.begin(), polys.end(), detail::isOdd) << "\n";
  } else {
    const size_t n = std::stoull(arg);
    if (n < 3) {
      throw std::invalid_argument("invalid vertex count");
    }
    out << std::count_if(polys.begin(), polys.end(),
        [n](const Polygon& p) {
          return p.points.size() == n;
        }) << "\n";
  }
}

void
cmdEcho(std::ostream& out,
        std::vector< Polygon >& polys,
        std::istream& in)
{
  Polygon target;
  if (!(in >> target)) {
    throw std::invalid_argument("invalid polygon argument");
  }

  const size_t count = static_cast< size_t >(
      std::count(polys.begin(), polys.end(), target));

  std::vector< Polygon > result;
  result.reserve(polys.size() + count);

  std::for_each(polys.begin(), polys.end(),
      [&result, &target](const Polygon& p) {
        result.push_back(p);
        if (p == target) {
          result.push_back(p);
        }
      });

  polys = std::move(result);
  out << count << "\n";
}

void
cmdRmecho(std::ostream& out,
          std::vector< Polygon >& polys,
          std::istream& in)
{
  Polygon target;
  if (!(in >> target)) {
    throw std::invalid_argument("invalid polygon argument");
  }

  const size_t before = polys.size();

  const auto newEnd = std::unique(polys.begin(), polys.end(),
      [&target](const Polygon& a, const Polygon& b) {
        return a == target && b == target;
      });

  polys.erase(newEnd, polys.end());
  out << (before - polys.size()) << "\n";
}

}
