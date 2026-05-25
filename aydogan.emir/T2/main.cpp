#include "data_struct.hpp"

#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>

int main()
{
  using aydogan::DataStruct;

  std::vector< DataStruct > data;

  using inputIterator = std::istream_iterator< DataStruct >;
  using outputIterator = std::ostream_iterator< DataStruct >;

  std::copy(
    inputIterator{ std::cin },
    inputIterator{},
    std::back_inserter(data)
  );

  std::sort(data.begin(), data.end(), aydogan::compareData);

  std::copy(
    data.begin(),
    data.end(),
    outputIterator{ std::cout, "\n" }
  );

  return 0;
}
