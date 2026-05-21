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

alekseev::Polygon::Polygon():
  points_(std::vector< Point >())
{
}

alekseev::Polygon::Polygon(const std::vector< Point > & points):
  points_(points)
{
  using namespace std::placeholders;
  Point pc = std::accumulate(points_.begin(), points_.end(), Point{0, 0});
  double xc = pc.x / static_cast< double >(size());
  double yc = pc.y / static_cast< double >(size());
  std::sort(points_.begin(), points_.end(), std::bind(less_angle, _1, _2, xc, yc));
}

double alekseev::Polygon::area() const
{
  int area = 0;
  for (size_t i = 0; i < size(); ++i) {
    size_t j = (i + 1) % size();
    area += points_[i].x * points_[j].y;
    area -= points_[j].x * points_[i].y;
  }
  return abs(area) / 2.0;
}

size_t alekseev::Polygon::size() const
{
  return points_.size();
}

double alekseev::Polygon::operator+(const Polygon & other) const
{
  return area() + other.area();
}

double alekseev::operator+(double a, const Polygon & b)
{
  return a + b.area();
}

std::istream & alekseev::operator>>(std::istream & is, Polygon & p)
{
  if (!is) {
    return is;
  }
  std::string line;
  std::getline(is, line);
  std::istringstream iss(line);
  int n = 0;
  iss >> n;
  if (n <= 0 || iss.fail()) {
    is.setstate(std::ios::failbit);
    return is;
  }
  std::istream_iterator< Point > begin(iss), end{};
  std::vector< Point > res;
  std::copy(begin, end, std::back_inserter(res));
  if (res.size() != n || iss.fail()) {
    is.setstate(std::ios::failbit);
  }
  if (is) {
    p = Polygon(res);
  }
  return is;
}

alekseev::Polygon alekseev::from_string(const std::string & line)
{
  Polygon res;
  std::istringstream iss(line);
  int n = 0;
  iss >> n;
  if (n <= 0 || iss.fail()) {
    return res;
  }
  std::vector< Point > points;
  std::istream_iterator< Point > begin(iss), end{};
  std::copy(begin, end, std::back_inserter(points));
  if (iss.eof() && points.size() == n) {
    res = Polygon(points);
  }
  return res;
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
