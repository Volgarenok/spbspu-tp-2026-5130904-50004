#ifndef DATASTRUCT_HPP
#define DATASTRUCT_HPP

#include <istream>
#include <ostream>
#include <string>
#include <utility>

namespace alberto {

struct DataStruct
{
  long long                                  key1 = 0;
  std::pair< long long, unsigned long long > key2 = {0, 0};
  std::string                                key3 = {};
};
std::istream& operator>>(std::istream& in, DataStruct& ds);
std::ostream& operator<<(std::ostream& out, const DataStruct& ds);

bool operator<(const DataStruct& a, const DataStruct& b);

}

#endif
