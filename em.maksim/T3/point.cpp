#include "point.hpp"

namespace em
{
  std::istream & operator>>(std::istream & is, Point & p)
  {
    char open = '\0';
    char semicolon = '\0';
    char close = '\0';
    is >> open >> p.x >> semicolon >> p.y >> close;
    if (open != '(' || semicolon != ';' || close != ')')
    {
      is.setstate(std::ios::failbit);
    }
    return is;
  }

  std::ostream & operator<<(std::ostream & os, const Point & p)
  {
    os << "(" << p.x << ";" << p.y << ")";
    return os;
  }
}
