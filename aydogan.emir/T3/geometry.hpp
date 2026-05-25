#ifndef GEOMETRY_HPP
#define GEOMETRY_HPP

#include <cstddef>
#include <iosfwd>
#include <vector>

namespace aydogan
{
  struct Point
  {
    int x;
    int y;
  };

  struct Polygon
  {
    std::vector< Point > points;
  };

  struct DelimiterIO
  {
    char expected;
  };

  struct PointCountIO
  {
    std::size_t& value;
  };

  std::istream& operator>>(std::istream& input, DelimiterIO&& data);
  std::istream& operator>>(std::istream& input, Point& point);
  std::istream& operator>>(std::istream& input, Polygon& polygon);

  std::ostream& operator<<(std::ostream& output, const Point& point);
  std::ostream& operator<<(std::ostream& output, const Polygon& polygon);

  bool operator==(const Point& left, const Point& right);
  bool operator==(const Polygon& left, const Polygon& right);

  double getArea(const Polygon& polygon);
  bool hasEvenVertexCount(const Polygon& polygon);
  bool hasOddVertexCount(const Polygon& polygon);
  bool hasVertexCount(const Polygon& polygon, std::size_t count);
  std::size_t getVertexCount(const Polygon& polygon);

  bool isPermutationOf(const Polygon& left, const Polygon& right);
  bool hasRightAngle(const Polygon& polygon);
}

#endif
