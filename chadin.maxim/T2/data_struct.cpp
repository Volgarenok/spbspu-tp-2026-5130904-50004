#include "data_struct.hpp"
#include "io_formats.hpp"
#include <iomanip>

namespace chadin {
  DataStruct::DataStruct():
    key1(0.0),
    key2(0),
    key3(""),
    isValid(false)
  {
  }

  bool operator<(const DataStruct& lhs, const DataStruct& rhs)
  {
    if (lhs.key1 != rhs.key1) {
      return lhs.key1 < rhs.key1;
    } else if (lhs.key2 != rhs.key2) {
      return lhs.key2 < rhs.key2;
    }
    return lhs.key3.length() < rhs.key3.length();
  }
