#ifndef DATA_STRUCT_HPP
#define DATA_STRUCT_HPP

#include <string>
#include <iostream>

namespace ali
{
  struct DataStruct
  {
    char key1;
    double key2;
    std::string key3;
  };

  bool operator<(const DataStruct & a, const DataStruct & b);

  std::istream & operator>>(std::istream & in, DataStruct & data);

  std::ostream & operator<<(std::ostream & out, const DataStruct & data);
}

#endif
