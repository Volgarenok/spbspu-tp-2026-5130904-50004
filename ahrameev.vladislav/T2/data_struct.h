#ifndef DATA_STRUCT_H
#define DATA_STRUCT_H

#include <iostream>
#include <string>

namespace ahrameev
{
  struct DataStruct
  {
    double key1;
    long long key2;
    std::string key3;
  };

  bool operator<(const DataStruct& lhs, const DataStruct& rhs);
  std::ostream& operator<<(std::ostream& out, const DataStruct& src);
}

#endif