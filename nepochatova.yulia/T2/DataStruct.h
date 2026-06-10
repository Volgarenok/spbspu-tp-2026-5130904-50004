#ifndef DATASTRUCT_H
#define DATASTRUCT_H

#include <string>
#include <iosfwd>

namespace nepochatova {

  struct DataStruct {
    long long key1;           // SLL_LIT
    unsigned long long key2;  // ULL_LIT
    std::string key3;         // String in quotes
  };

}
#endif