#include <iostream>

#include "data_struct.h"

int main()
{
  ahrameev::DataStruct test = {1.5, 42LL, "hello"};
  std::cout << test << "\n";
}