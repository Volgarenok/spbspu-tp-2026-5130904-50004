#include "Polygon.h"
#include <sstream>
#include<string>

#include "../../../../../../Program Files/JetBrains/CLion 2025.2/bin/mingw/lib/gcc/x86_64-w64-mingw32/13.1.0/include/c++/iterator"

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
