#include "DataStruct.hpp"
#include "Formatters.hpp"

namespace pozdeev
{
  std::istream& operator>>(std::istream& in, DataStruct& dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }

    DataStruct temp{0.0, 0ull, ""};
    bool hasKey1 = false;
    bool hasKey2 = false;
    bool hasKey3 = false;

    in >> DelimiterIO{'('};

    for (int i = 0; i < 3; ++i)
    {
      in >> DelimiterIO{':'};
      std::string key;
      in >> key;

      if (key == "key1")
      {
        in >> DoubleLiteralIO{temp.key1};
        hasKey1 = true;
      }
      else if (key == "key2")
      {
        in >> UllHexIO{temp.key2};
        hasKey2 = true;
      }
      else if (key == "key3")
      {
        in >> StringIO{temp.key3};
        hasKey3 = true;
      }
      else
      {
        in.setstate(std::ios::failbit);
      }
    }

    in >> DelimiterIO{':'} >> DelimiterIO{')'};

    if (in && hasKey1 && hasKey2 && hasKey3)
    {
      dest = temp;
    }
    else
    {
      in.setstate(std::ios::failbit);
    }

    return in;
  }

  std::ostream& operator<<(std::ostream& out, const DataStruct& src)
  {
    std::ostream::sentry sentry(out);
    if (!sentry)
    {
      return out;
    }

    out << "(:key1 " << DoubleLiteralOut{src.key1}
        << ":key2 " << UllHexOut{src.key2}
        << ":key3 " << StringOut{src.key3} << ":)";
    return out;
  }

  bool compareDataStructs(const DataStruct& lhs, const DataStruct& rhs)
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
}
