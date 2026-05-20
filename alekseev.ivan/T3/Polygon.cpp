#include "Polygon.h"

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
