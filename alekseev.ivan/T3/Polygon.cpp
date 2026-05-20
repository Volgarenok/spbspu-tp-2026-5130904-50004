#include "Polygon.h"
#include <sstream>
#include <string>
#include <iterator>
#include <numeric>
#include <cmath>
#include <functional>
#include <algorithm>

alekseev::Point alekseev::Point::operator+(const Point & other) const
{
  return {x + other.x, y + other.y};
}

alekseev::Point alekseev::Point::operator-(const Point & other) const
{
  return {x - other.x, y - other.y};
}

bool alekseev::less_angle(const Point & a, const Point & b, double xc, double yc)
{
  return std::atan2(a.y - yc, a.x - xc) < std::atan2(b.y - yc, b.x - xc);
}

std::istream & alekseev::operator>>(std::istream & is, Point p)
{
  if (!is) {
    return is;
  }
  is >> expected{"("} >> p.x >> expected{";"};
  is >> p.y >> expected{")"};
  return is;
}

std::ostream & alekseev::operator<<(std::ostream & os, const Point & p)
{
  if (!os) {
    return os;
  }
  os << "(" << p.x << ";" << p.y << ")";
  return os;
}

double alekseev::Polygon::area()
{
  using namespace std::placeholders;
  Point pc = std::accumulate(points.begin(), points.end(), Point{0, 0});
  double xc = pc.x / static_cast< double >(count());
  double yc = pc.y / static_cast< double >(count());
  std::sort(points.begin(), points.end(), std::bind(less_angle, _1, _2, xc, yc));
  int area = 0;
  for (size_t i = 0; i < count(); ++i) {
    size_t j = (i + 1) % count();
    area += points[i].x * points[j].y;
    area -= points[j].x * points[i].y;
  }
  return abs(area) / 2.0;
}

size_t alekseev::Polygon::count() const
{
  return points.size();
}

std::istream & alekseev::operator>>(std::istream & is, Polygon & p)
{
  if (!is) {
    return is;
  }
  std::string line;
  std::getline(is, line);
  while (line.empty()) {
    std::getline(is, line);
  }
  std::istringstream iss(line);
  int n = 0;
  iss >> n;
  if (n <= 0) {
    is.setstate(std::ios::failbit);
    return is;
  }
  std::istream_iterator< Point > begin(iss), end{};
  std::copy(begin, end, std::back_inserter(p.points));
  if (p.points.size() != n || iss.fail()) {
    is.setstate(std::ios::failbit);
  }
  return is;
}

std::istream & alekseev::operator>>(std::istream & is, expected e)
{
  if (!is) {
    return is;
  }
  char c = 0;
  for (size_t i = 0; i < e.source.length(); ++i) {
    is >> c;
    if (c != e.source[i]) {
      is.setstate(std::ios_base::failbit);
      return is;
    }
  }
  return is;
}

alekseev::IOGuard::IOGuard(std::basic_ios< char > & stream):
  stream_(stream),
  precision_(stream.precision()),
  width_(stream.width()),
  flags_(stream.flags()),
  fill_(stream.fill())
{
}

alekseev::IOGuard::~IOGuard()
{
  stream_.precision(precision_);
  stream_.width(width_);
  stream_.flags(flags_);
  stream_.fill(fill_);
}
