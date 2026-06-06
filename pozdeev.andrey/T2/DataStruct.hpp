#ifndef DATASTRUCT_HPP
#define DATASTRUCT_HPP

#include <iostream>
#include <string>

namespace pozdeev
{
  struct DataStruct
  {
    double key1;
    unsigned long long key2;
    std::string key3;
  };

  std::istream& operator>>(std::istream& in, DataStruct& dest);
  std::ostream& operator<<(std::ostream& out, const DataStruct& src);
  bool compareDataStructs(const DataStruct& lhs, const DataStruct& rhs);
}

#endif
