#include "geometry.hpp"

#include <algorithm>
#include <cmath>
#include <iostream>
#include <iterator>
#include <numeric>

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
