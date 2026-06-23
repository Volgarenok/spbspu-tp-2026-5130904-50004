#include <iostream>
#include <vector>

#include "data_struct.h"

int main()
{
  std::vector< ahrameev::DataStruct > data;
  ahrameev::DataStruct temp = {0.0, 0LL, ""};

  while (std::cin >> temp)
  {
    data.push_back(temp);
  }

  for (size_t i = 0; i < data.size(); ++i)
  {
    std::cout << data[i] << "\n";
  }
}