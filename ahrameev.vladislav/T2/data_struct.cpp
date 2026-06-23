#include "data_struct.h"

#include <iomanip>
#include <iostream>
#include <limits>
#include <string>

namespace
{
  class IOguard
  {
  public:
    explicit IOguard(std::basic_ios< char >& stream):
      stream_(stream),
      width_(stream.width()),
      precision_(stream.precision()),
      fmt_(stream.flags()),
      fill_(stream.fill())
    {
    }

    ~IOguard()
    {
      stream_.width(width_);
      stream_.precision(precision_);
      stream_.flags(fmt_);
      stream_.fill(fill_);
    }

  private:
    std::basic_ios< char >& stream_;
    std::streamsize width_;
    std::streamsize precision_;
    std::basic_ios< char >::fmtflags fmt_;
    char fill_;
  };

  struct DelimiterIO
  {
    char exp;
  };

  struct DoubleLitIO
  {
    double& ref;
  };

  struct SignedLongLongLitIO
  {
    long long& ref;
  };

  struct QuotedStringIO
  {
    std::string& ref;
  };

  bool isSpace(char symbol)
  {
    return (symbol == ' ') || (symbol == '\t')
      || (symbol == '\n') || (symbol == '\r');
  }

  void skipSpaces(std::istream& input)
  {
    while (input && isSpace(static_cast< char >(input.peek())))
    {
      input.get();
    }
  }

  std::istream& operator>>(std::istream& input, DelimiterIO&& dest)
  {
    char symbol = '\0';
    input >> symbol;
    if (input && (symbol != dest.exp))
    {
      input.setstate(std::ios::failbit);
    }
    return input;
  }

  std::istream& operator>>(std::istream& input, DoubleLitIO&& dest)
  {
    double value = 0.0;
    input >> value;
    if (!input)
    {
      return input;
    }
    char suffix = '\0';
    input >> suffix;
    if (input && ((suffix == 'd') || (suffix == 'D')))
    {
      dest.ref = value;
    }
    else
    {
      input.setstate(std::ios::failbit);
    }
    return input;
  }

  std::istream& operator>>(std::istream& input, SignedLongLongLitIO&& dest)
  {
    long long value = 0;
    input >> value;
    if (!input)
    {
      return input;
    }
    char firstSuffix = '\0';
    char secondSuffix = '\0';
    input >> firstSuffix >> secondSuffix;
    bool isLower = (firstSuffix == 'l') && (secondSuffix == 'l');
    bool isUpper = (firstSuffix == 'L') && (secondSuffix == 'L');
    if (input && (isLower || isUpper))
    {
      dest.ref = value;
    }
    else
    {
      input.setstate(std::ios::failbit);
    }
    return input;
  }

  std::istream& operator>>(std::istream& input, QuotedStringIO&& dest)
  {
    input >> DelimiterIO{'"'};
    if (!input)
    {
      return input;
    }
    return std::getline(input, dest.ref, '"');
  }
}

std::istream& ahrameev::operator>>(std::istream& in, DataStruct& dest)
{
  while (in)
  {
    DataStruct temp = {0.0, 0LL, ""};
    bool hasKey1 = false;
    bool hasKey2 = false;
    bool hasKey3 = false;

    in >> DelimiterIO{'('} >> DelimiterIO{':'};
    if (in)
    {
      while (in)
      {
        skipSpaces(in);
        if (in.peek() == ')')
        {
          break;
        }

        std::string label = "";
        in >> label;
        if (!in)
        {
          break;
        }

        if (label == "key1")
        {
          in >> DoubleLitIO{temp.key1};
          hasKey1 = true;
        }
        else if (label == "key2")
        {
          in >> SignedLongLongLitIO{temp.key2};
          hasKey2 = true;
        }
        else if (label == "key3")
        {
          in >> QuotedStringIO{temp.key3};
          hasKey3 = true;
        }
        else
        {
          in.setstate(std::ios::failbit);
          break;
        }

        if (in)
        {
          in >> DelimiterIO{':'};
        }
      }

      if (in)
      {
        skipSpaces(in);
        in >> DelimiterIO{')'};
      }
    }

    if (in && hasKey1 && hasKey2 && hasKey3)
    {
      dest = temp;
      return in;
    }

    in.clear();
    in.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
  }
  return in;
}

std::ostream& ahrameev::operator<<(std::ostream& out, const DataStruct& src)
{
  IOguard guard(out);
  out << "(:key1 "
      << std::fixed << std::setprecision(1) << src.key1 << "d"
      << ":key2 " << src.key2 << "ll"
      << ":key3 \"" << src.key3 << "\":)";
  return out;
}

bool ahrameev::operator<(const DataStruct& lhs, const DataStruct& rhs)
{
  if (lhs.key1 != rhs.key1)
  {
    return lhs.key1 < rhs.key1;
  }
  if (lhs.key2 != rhs.key2)
  {
    return lhs.key2 < rhs.key2;
  }
  return lhs.key3.length() < rhs.key3.length();
}