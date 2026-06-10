#include "DataStruct.h"
#include "IOGuard.h"
#include <iostream>

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
}