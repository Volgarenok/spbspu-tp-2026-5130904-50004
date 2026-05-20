#ifndef POLYGON_H
#define POLYGON_H

#include <iostream>
#include <vector>

namespace alekseev {
  struct Point {
    int x, y;
  };

  std::istream & operator>>(std::istream & is, Point p);
  std::ostream & operator<<(std::ostream & os, const Point & p);

  struct Polygon {
    std::vector< Point > points;
  };

  std::istream & operator>>(std::istream & is, Polygon & p);
  std::ostream & operator<<(std::ostream & os, const Polygon & p);

  struct expected {
    std::string source;
  };

  std::istream & operator>>(std::istream & is, expected e);

  struct IOGuard {
    explicit IOGuard(std::basic_ios< char > & stream);
    ~IOGuard();

    private:
      std::basic_ios< char > & stream_;
      std::streamsize precision_;
      std::streamsize width_;
      std::basic_ios< char >::fmtflags flags_;
      char fill_;
  };
}

#endif
