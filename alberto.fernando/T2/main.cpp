#include "Datastruct.hpp"
#include <algorithm>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>
int main()
{
  std::vector< alberto::DataStruct > data;
  alberto::DataStruct                ds;
  while (!std::cin.eof()) {
    if (std::cin >> ds) {
      data.push_back(ds);
    } else {
      std::cin.clear();
      std::string discard;
      std::getline(std::cin, discard);
    }
  }
  std::sort(data.begin(), data.end());
  std::copy(
      data.cbegin(),
      data.cend(),
      std::ostream_iterator< alberto::DataStruct >(std::cout, "\n"));
  return 0;
}
