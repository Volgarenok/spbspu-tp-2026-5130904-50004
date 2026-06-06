#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
#include "DataStruct.hpp"

int main()
{
  std::vector< pozdeev::DataStruct > data;

  while (!std::cin.eof())
  {
    std::copy(
      std::istream_iterator< pozdeev::DataStruct >(std::cin),
      std::istream_iterator< pozdeev::DataStruct >(),
      std::back_inserter(data)
    );
    if (std::cin.fail() && !std::cin.eof())
    {
      std::cin.clear();
      std::cin.ignore(1);
    }
  }

  std::sort(data.begin(), data.end(), pozdeev::compareDataStructs);

  std::copy(
    data.begin(),
    data.end(),
    std::ostream_iterator< pozdeev::DataStruct >(std::cout, "\n")
  );

  return 0;
}
