#ifndef DATASTRUCT_H
#define DATASTRUCT_H

#include <string>
#include <iosfwd>

namespace nepochatova {
  enum Field {
    KEY1 = 1,
    KEY2 = 2,
    KEY3 = 4,
    ALL  = KEY1 | KEY2 | KEY3
};

  struct DataStruct {
    long long key1;
    unsigned long long key2;
    std::string key3;
  };

  struct KeyValueInp {
    const std::string& key;
    int& mask;
    DataStruct& ds;
  };

  std::istream& operator>>(std::istream& in, DataStruct& dest);
  std::ostream& operator<<(std::ostream& out, const DataStruct& src);
  bool operator<(const DataStruct& lhs, const DataStruct& rhs);

}
#endif
