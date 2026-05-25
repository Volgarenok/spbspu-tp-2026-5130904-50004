#include "data_struct.hpp"
#include "iofmtguard.hpp"

#include <algorithm>
#include <cctype>
#include <iomanip>
#include <iostream>
#include <limits>
#include <sstream>

namespace
{
  bool readDataLine(std::istream& input, aydogan::DataStruct& data)
  {
    aydogan::DataStruct temporary{};
    bool hasKey1 = false;
    bool hasKey2 = false;
    bool hasKey3 = false;

    input >> aydogan::DelimiterIO{ '(' } >> aydogan::DelimiterIO{ ':' };

    for (std::size_t i = 0; input && i < 3; ++i)
    {
      std::string label;

      while (input)
      {
        int next = input.peek();

        if (next == ' ' || next == '\t')
        {
          input.get();
        }
        else
        {
          break;
        }
      }

      std::getline(input, label, ' ');

      if (!input)
      {
        return false;
      }

      if (label == "key1")
      {
        if (hasKey1)
        {
          return false;
        }

        input >> aydogan::UllLiteralIO{ temporary.key1 } >> aydogan::DelimiterIO{ ':' };
        hasKey1 = true;
      }
      else if (label == "key2")
      {
        if (hasKey2)
        {
          return false;
        }

        input >> aydogan::UllBinaryIO{ temporary.key2 } >> aydogan::DelimiterIO{ ':' };
        hasKey2 = true;
      }
      else if (label == "key3")
      {
        if (hasKey3)
        {
          return false;
        }

        input >> aydogan::StringIO{ temporary.key3 } >> aydogan::DelimiterIO{ ':' };
        hasKey3 = true;
      }
      else
      {
        return false;
      }
    }

    input >> aydogan::DelimiterIO{ ')' };
    input >> std::ws;

    if (!input || !input.eof() || !hasKey1 || !hasKey2 || !hasKey3)
    {
      return false;
    }

    data = temporary;
    return true;
  }
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

    if (!input.get(current))
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

  if (!input.get(zero) || !input.get(letter))
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

std::istream& aydogan::operator>>(std::istream& input, DataStruct& data)
{
  std::istream::sentry sentry(input);

  if (!sentry)
  {
    return input;
  }

  std::string line;

  while (std::getline(input, line))
  {
    std::istringstream lineInput(line);
    DataStruct temporary{};

    if (readDataLine(lineInput, temporary))
    {
      data = temporary;
      return input;
    }
  }

  return input;
}

std::ostream& aydogan::operator<<(std::ostream& output, const DataStruct& data)
{
  std::ostream::sentry sentry(output);

  if (!sentry)
  {
    return output;
  }

  IOFmtGuard guard(output);

  output << "(:";
  output << "key1 " << data.key1 << "ull:";
  output << "key2 0b";

  if (data.key2 == 0)
  {
    output << "0";
  }
  else
  {
    std::string binary;

    unsigned long long value = data.key2;

    while (value > 0)
    {
      binary += static_cast< char >('0' + value % 2);
      value /= 2;
    }

    std::reverse(binary.begin(), binary.end());
    output << binary;
  }

  output << ":";
  output << "key3 " << std::quoted(data.key3) << ":";
  output << ")";

  return output;
}

bool aydogan::compareData(const DataStruct& left, const DataStruct& right)
{
  if (left.key1 != right.key1)
  {
    return left.key1 < right.key1;
  }

  if (left.key2 != right.key2)
  {
    return left.key2 < right.key2;
  }

  return left.key3.length() < right.key3.length();
}
