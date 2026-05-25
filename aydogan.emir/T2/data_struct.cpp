#include "data_struct.hpp"
#include "iofmtguard.hpp"

#include <algorithm>
#include <cctype>
#include <iomanip>
#include <iostream>
#include <limits>
#include <sstream>

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

std::istream& aydogan::operator>>(std::istream& input, LabelIO&& data)
{
  std::istream::sentry sentry(input);

  if (!sentry)
  {
    return input;
  }

  for (char expectedSymbol: data.expected)
  {
    char current = '\0';
    input >> current;

    if (!input || current != expectedSymbol)
    {
      input.setstate(std::ios::failbit);
      return input;
    }
  }

  return input;
}

std::istream& aydogan::operator>>(std::istream& input, StringIO&& data)
{
  std::istream::sentry sentry(input);

  if (!sentry)
  {
    return input;
  }

  return std::getline(input >> DelimiterIO{ '"' }, data.value, '"');
}
