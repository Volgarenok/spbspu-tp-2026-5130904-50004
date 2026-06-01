#include "DataStruct.hpp"
#include "subTypes.hpp"

namespace vasilenko {

  bool operator<(const DataStruct& lhs, const DataStruct& rhs) {
    if (lhs.key1 != rhs.key1) {
      return lhs.key1 < rhs.key1;
    }
    if (lhs.key2 != rhs.key2) {
      return lhs.key2 < rhs.key2;
    }
    return lhs.key3.length() < rhs.key3.length();
  }

  std::istream& operator>>(std::istream& in, DataStruct& dest) {
    std::istream::sentry sentry(in);
    if (!sentry) {
      return in;
    }

    DataStruct input;
    in >> DelimiterI{'('} >> DelimiterI{':'};

    bool hasKey1 = false;
    bool hasKey2 = false;
    bool hasKey3 = false;

    for (int i = 0; i < 3; ++i) {
      char k = '0', e = '0', y = '0', num = '0';
      in >> k >> e >> y >> num;
      if (k != 'k' || e != 'e' || y != 'y') {
        in.setstate(std::ios::failbit);
        return in;
      }

      if (num == '1' && !hasKey1) {
        in >> DoubleSciI{input.key1};
        hasKey1 = true;
      } else if (num == '2' && !hasKey2) {
        in >> SignedLongLongI{input.key2};
        hasKey2 = true;
      } else if (num == '3' && !hasKey3) {
        in >> StringI{input.key3};
        hasKey3 = true;
      } else {
        in.setstate(std::ios::failbit);
        return in;
      }
      in >> DelimiterI{':'};
    }

    in >> DelimiterI{')'};

    if (in && hasKey1 && hasKey2 && hasKey3) {
      dest = input;
    } else {
      in.setstate(std::ios::failbit);
    }

    return in;
  }

  std::ostream& operator<<(std::ostream& out, const DataStruct& dest) {
    std::ostream::sentry sentry(out);
    if (!sentry) {
      return out;
    }
    out << "(:key1 " << DoubleSciO{dest.key1}
        << ":key2 " << SignedLongLongO{dest.key2}
        << ":key3 " << StringO{dest.key3} << ":)";
    return out;
  }

}
