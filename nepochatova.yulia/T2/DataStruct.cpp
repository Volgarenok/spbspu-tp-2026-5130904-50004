#include "DataStruct.h"
#include "IOGuard.h"
#include <iostream>
#include <limits>

namespace nepochatova {
  std::istream& parseField(std::istream& in, const std::string& key, int& mask, DataStruct& ds)
  {
    Field field = static_cast<Field>(0);
    if (key == "key1")      field = KEY1;
    else if (key == "key2") field = KEY2;
    else if (key == "key3") field = KEY3;
    else {
      in.setstate(std::ios_base::failbit);
      return in;
    }
    if (mask & field) {
      in.setstate(std::ios_base::failbit);
      return in;
    }
    switch (field) {
      case KEY1: in >> SllLitIO{ds.key1}; break;
      case KEY2: in >> UllLitIO{ds.key2}; break;
      case KEY3: in >> StringIO{ds.key3}; break;
      default:   in.setstate(std::ios_base::failbit); return in;
    }
    if (in) mask |= field;
    return in;
  }

  std::istream& operator>>(std::istream& in, DataStruct& dest)
  {
    std::istream::sentry s(in);
    if (!s) return in;

    DataStruct tmp{};
    char dummy = 0;
    int mask = 0;
    std::string k1, k2, k3;

    in >> DelimiterIO{'(', dummy}
    >> DelimiterIO{':', dummy} >> k1 >> KeyValueInp{k1, mask, tmp} >> DelimiterIO{':', dummy}
    >> DelimiterIO{':', dummy} >> k2 >> KeyValueInp{k2, mask, tmp} >> DelimiterIO{':', dummy}
    >> DelimiterIO{':', dummy} >> k3 >> KeyValueInp{k3, mask, tmp} >> DelimiterIO{':', dummy}
    >> DelimiterIO{')', dummy};

    if (in && mask == ALL) {
      dest = tmp;
    } else {
      in.clear();
      in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      in >> dest;
    }
    return in;
  }

  std::ostream& operator<<(std::ostream& out, const DataStruct& src)
  {
    std::ostream::sentry s(out);
    if (!s) return out;
    IOguard guard(out);
    out << "(:key1 " << SllLitIO{src.key1}
    << ":key2 " << UllLitIO{src.key2}
    << ":key3 \"" << src.key3 << "\":)";
    return out;
  }

  bool operator<(const DataStruct& lhs, const DataStruct& rhs)
  {
    bool c1 = key1_less(lhs.key1, rhs.key1);
    bool c1_eq = key1_equal(lhs.key1, rhs.key1);
    bool c2 = key2_less(lhs.key2, rhs.key2);
    bool c2_eq = key2_equal(lhs.key2, rhs.key2);
    bool c3 = key3_less(lhs.key3, rhs.key3);

    return c1 || (c1_eq && c2) || (c1_eq && c2_eq && c3);
  }

  bool key1_less(long long a, long long b)
  {
    return a < b;
  }
  bool key1_equal(long long a, long long b)
  {
    return a == b;
  }
  bool key2_less(unsigned long long a, unsigned long long b)
  {
    return a < b;
  }
  bool key2_equal(unsigned long long a, unsigned long long b)
  {
    return a == b;
  }
  bool key3_less(const std::string& a, const std::string& b)
  {
    return a.size() < b.size();
  }
}
