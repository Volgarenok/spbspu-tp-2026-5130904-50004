#include "data-struct.hpp"

#include <iomanip>

namespace ali
{
  bool operator<(const DataStruct & a, const DataStruct & b)
  {
    if (a.key1 != b.key1)
    {
      return a.key1 < b.key1;
    }
    if (a.key2 != b.key2)
    {
      return a.key2 < b.key2;
    }
    return a.key3.length() < b.key3.length();
  }

  std::istream & operator>>(std::istream & in, DataStruct & data)
  {
    DataStruct temp{};
    char c = '\0';
    std::string key;

    in >> c;
    if (!in || c != '(')
    {
      in.setstate(std::ios::failbit);
      return in;
    }

    in >> c;
    if (!in || c != ':')
    {
      in.setstate(std::ios::failbit);
      return in;
    }

    in >> key;
    if (key != "key1")
    {
      in.setstate(std::ios::failbit);
      return in;
    }

    in >> c;
    if (c != '\'')
    {
      in.setstate(std::ios::failbit);
      return in;
    }

    in >> temp.key1;

    in >> c;
    if (c != '\'')
    {
      in.setstate(std::ios::failbit);
      return in;
    }

    in >> c;
    if (c != ':')
    {
      in.setstate(std::ios::failbit);
      return in;
    }

    in >> key;
    if (key != "key2")
    {
      in.setstate(std::ios::failbit);
      return in;
    }

    in >> temp.key2;

    in >> c;
    if (c != ':')
    {
      in.setstate(std::ios::failbit);
      return in;
    }

    in >> key;
    if (key != "key3")
    {
      in.setstate(std::ios::failbit);
      return in;
    }

    in >> std::quoted(temp.key3);

    in >> c;
    if (c != ':')
    {
      in.setstate(std::ios::failbit);
      return in;
    }

    in >> c;
    if (c != ')')
    {
      in.setstate(std::ios::failbit);
      return in;
    }

    data = temp;
    return in;
  }

  std::ostream & operator<<(std::ostream & out, const DataStruct & data)
  {
    out << "(:key1 '" << data.key1 << "':";
    out << "key2 "
    << std::scientific
    << std::setprecision(1)
    << data.key2
    << ":";
    out << "key3 \"" << data.key3 << "\":)";
    return out;
  }
}
