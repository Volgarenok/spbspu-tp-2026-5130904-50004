#ifndef POLYGON_H
#define POLYGON_H

#include <iostream>
#include <vector>

namespace alekseev {
  struct Point {
    int x, y;

    Point operator+(const Point & other) const;
    Point operator-(const Point & other) const;
  };

  bool less_angle(const Point & a, const Point & b, double xc, double yc);
  std::istream & operator>>(std::istream & is, Point p);
  std::ostream & operator<<(std::ostream & os, const Point & p);

  struct Polygon {
    std::vector< Point > points;

    double area();
    size_t count() const;
  };

  std::istream & operator>>(std::istream & is, Polygon & p);

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
