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

std::istream& aydogan::operator>>(std::istream& input, UllLiteralIO&& data)
{
  std::istream::sentry sentry(input);

  if (!sentry)
  {
    return input;
  }

  unsigned long long value = 0;
  input >> value;

  if (!input)
  {
    return input;
  }

  std::string suffix;
  suffix.reserve(3);

  for (std::size_t i = 0; i < 3; ++i)
  {
    char current = '\0';
    input >> current;

    if (!input)
    {
      return input;
    }

    suffix += static_cast< char >(std::tolower(static_cast< unsigned char >(current)));
  }

  if (suffix != "ull")
  {
    input.setstate(std::ios::failbit);
    return input;
  }

  data.value = value;
  return input;
}

std::istream& aydogan::operator>>(std::istream& input, UllBinaryIO&& data)
{
  std::istream::sentry sentry(input);

  if (!sentry)
  {
    return input;
  }

  char zero = '\0';
  char letter = '\0';

  input >> zero >> letter;

  if (!input)
  {
    return input;
  }

  if (zero != '0' || (letter != 'b' && letter != 'B'))
  {
    input.setstate(std::ios::failbit);
    return input;
  }

  unsigned long long value = 0;
  bool hasDigits = false;

  while (input)
  {
    int next = input.peek();

    if (next != '0' && next != '1')
    {
      break;
    }

    char current = '\0';
    input >> current;

    value = value * 2 + static_cast< unsigned long long >(current - '0');
    hasDigits = true;
  }

  if (!hasDigits)
  {
    input.setstate(std::ios::failbit);
    return input;
  }

  data.value = value;
  return input;
}
