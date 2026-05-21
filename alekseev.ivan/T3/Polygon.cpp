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

alekseev::Point alekseev::point_from_string(const std::string & s)
{
  Point p{0, 0};
  std::istringstream iss(s);
  iss >> expected{"("} >> p.x >> expected{";"};
  iss >> p.y >> expected{")"};
  if (iss.fail() && !iss.eof()) {
    throw std::invalid_argument("Wrong format");
  }
  return p;
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
}

alekseev::Polygon::Polygon(const std::vector< std::string > & args)
{
  size_t n = std::stoull(args.at(0));
  if (args.size() != n + 1) {
    throw std::invalid_argument("Wrong number of arguments");
  }
  std::vector< Point > points;
  std::transform(args.begin() + 1, args.end(), std::back_inserter(points),
      [](const std::string & s) {
        return point_from_string(s);
      });
  *this = Polygon(points);
}

double alekseev::Polygon::area() const
{
  long long area = 0;
  for (size_t i = 0; i < size(); ++i) {
    size_t j = (i + 1) % size();
    area += points_[i].x * points_[j].y;
    area -= points_[j].x * points_[i].y;
  }
  return std::abs(area) / 2.0;
}

size_t alekseev::Polygon::size() const
{
  return points_.size();
}

double alekseev::Polygon::operator+(const Polygon & other) const
{
  return area() + other.area();
}

bool alekseev::Polygon::is_inner(const Point & p) const
{
  bool inside = false;
  for (size_t i = 0; i < size(); ++i) {
    size_t j = (i + 1) % size();
    Point a = points_[i];
    Point b = points_[j];
    bool intersect = ((a.y < p.y) != (b.y < p.y));
    if (intersect) {
      double x_intersect = static_cast< double >(b.x - a.x) * (p.y - a.y) / static_cast< double >(b.
        y - a.y) + a.x;
      if (p.x < x_intersect) {
        inside = !inside;
      }
    }
  }
  return inside;
}

bool alekseev::Polygon::intersects(const Polygon & other) const
{
  return std::any_of(points_.begin(), points_.end(), [other](Point p) {
    return other.is_inner(p);
  });
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

bool alekseev::is_rectangle(const Polygon & p)
{
  if (p.size() != 4) {
    return false;
  }
  bool first_x = true, first_y = true;
  for (size_t i = 0; i < 4 && (first_x || first_y); ++i) {
    size_t j = (i + 1) % 4;
    if (i % 2 == 0) {
      first_x = p.points_[i].x == p.points_[j].x;
      first_y = p.points_[i].y == p.points_[j].y;
    } else {
      first_x = p.points_[i].y == p.points_[j].y;
      first_y = p.points_[i].x == p.points_[j].x;
    }
  }
  return first_x || first_y;
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
