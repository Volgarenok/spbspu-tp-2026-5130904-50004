#include "geometry.hpp"

#include <algorithm>
#include <cmath>
#include <iostream>
#include <iterator>
#include <numeric>
#include <vector>

namespace
{
  std::size_t getNextIndex(std::size_t index, std::size_t size)
  {
    return (index + 1) % size;
  }

  std::size_t getPreviousIndex(std::size_t index, std::size_t size)
  {
    return (index + size - 1) % size;
  }

  long long getDoubleAreaTerm(const aydogan::Polygon& polygon, std::size_t index)
  {
    std::size_t next = getNextIndex(index, polygon.points.size());

    const aydogan::Point& currentPoint = polygon.points[index];
    const aydogan::Point& nextPoint = polygon.points[next];

    return static_cast< long long >(currentPoint.x) * nextPoint.y
      - static_cast< long long >(currentPoint.y) * nextPoint.x;
  }

  bool hasRightAngleAt(const aydogan::Polygon& polygon, std::size_t index)
  {
    std::size_t previous = getPreviousIndex(index, polygon.points.size());
    std::size_t next = getNextIndex(index, polygon.points.size());

    const aydogan::Point& previousPoint = polygon.points[previous];
    const aydogan::Point& currentPoint = polygon.points[index];
    const aydogan::Point& nextPoint = polygon.points[next];

    long long firstX = previousPoint.x - currentPoint.x;
    long long firstY = previousPoint.y - currentPoint.y;
    long long secondX = nextPoint.x - currentPoint.x;
    long long secondY = nextPoint.y - currentPoint.y;

    return firstX * secondX + firstY * secondY == 0;
  }

  struct DoubleAreaTerm
  {
    const aydogan::Polygon& polygon;

    long long operator()(std::size_t index) const
    {
      return getDoubleAreaTerm(polygon, index);
    }
  };

  struct RightAngleAt
  {
    const aydogan::Polygon& polygon;

    bool operator()(std::size_t index) const
    {
      return hasRightAngleAt(polygon, index);
    }
  };
}

std::istream& aydogan::operator>>(std::istream& input, DelimiterIO&& data)
{
  std::istream::sentry sentry(input);

  if (!sentry)
  {
    return input;
  }

  char current = '\0';
  input >> current;

  if (input && current != data.expected)
  {
    input.setstate(std::ios::failbit);
  }

  return input;
}

std::istream& aydogan::operator>>(std::istream& input, Point& point)
{
  std::istream::sentry sentry(input);

  if (!sentry)
  {
    return input;
  }

  Point temporary{0, 0};

  input >> DelimiterIO{ '(' };
  input >> temporary.x;
  input >> DelimiterIO{ ';' };
  input >> temporary.y;
  input >> DelimiterIO{ ')' };

  if (input)
  {
    point = temporary;
  }

  return input;
}

std::istream& aydogan::operator>>(std::istream& input, Polygon& polygon)
{
  std::istream::sentry sentry(input);

  if (!sentry)
  {
    return input;
  }

  std::size_t count = 0;
  input >> count;

  if (!input || count < 3)
  {
    input.setstate(std::ios::failbit);
    return input;
  }

  Polygon temporary;
  temporary.points.resize(count);

  std::copy_n(
    std::istream_iterator< Point >(input),
    count,
    temporary.points.begin()
  );

  if (input)
  {
    polygon = temporary;
  }

  return input;
}

std::ostream& aydogan::operator<<(std::ostream& output, const Point& point)
{
  std::ostream::sentry sentry(output);

  if (!sentry)
  {
    return output;
  }

  output << "(" << point.x << ";" << point.y << ")";
  return output;
}

std::ostream& aydogan::operator<<(std::ostream& output, const Polygon& polygon)
{
  std::ostream::sentry sentry(output);

  if (!sentry)
  {
    return output;
  }

  output << polygon.points.size();

  if (!polygon.points.empty())
  {
    output << " ";
    std::copy(
      polygon.points.begin(),
      polygon.points.end(),
      std::ostream_iterator< Point >(output, " ")
    );
  }

  return output;
}

bool aydogan::operator==(const Point& left, const Point& right)
{
  return left.x == right.x && left.y == right.y;
}

bool aydogan::operator==(const Polygon& left, const Polygon& right)
{
  return left.points.size() == right.points.size()
    && std::equal(left.points.begin(), left.points.end(), right.points.begin());
}

double aydogan::getArea(const Polygon& polygon)
{
  std::vector< std::size_t > indexes(polygon.points.size());
  std::iota(indexes.begin(), indexes.end(), 0);

  std::vector< long long > terms(indexes.size());
  std::transform(
    indexes.begin(),
    indexes.end(),
    terms.begin(),
    DoubleAreaTerm{ polygon }
  );

  long long doubleArea = std::accumulate(terms.begin(), terms.end(), 0ll);

  return std::abs(static_cast< double >(doubleArea)) / 2.0;
}

bool aydogan::hasEvenVertexCount(const Polygon& polygon)
{
  return polygon.points.size() % 2 == 0;
}

bool aydogan::hasOddVertexCount(const Polygon& polygon)
{
  return polygon.points.size() % 2 != 0;
}

bool aydogan::hasVertexCount(const Polygon& polygon, std::size_t count)
{
  return polygon.points.size() == count;
}

std::size_t aydogan::getVertexCount(const Polygon& polygon)
{
  return polygon.points.size();
}

bool aydogan::isPermutationOf(const Polygon& left, const Polygon& right)
{
  return left.points.size() == right.points.size()
    && std::is_permutation(
      left.points.begin(),
      left.points.end(),
      right.points.begin()
    );
}

bool aydogan::hasRightAngle(const Polygon& polygon)
{
  std::vector< std::size_t > indexes(polygon.points.size());
  std::iota(indexes.begin(), indexes.end(), 0);

  return std::any_of(
    indexes.begin(),
    indexes.end(),
    RightAngleAt{ polygon }
  );
}
