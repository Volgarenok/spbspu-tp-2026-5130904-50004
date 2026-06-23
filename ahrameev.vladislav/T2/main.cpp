#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>

#include "data_struct.h"

int main()
{
  std::vector< ahrameev::DataStruct > data;

  using InputIterator = std::istream_iterator< ahrameev::DataStruct >;
  std::copy(InputIterator{std::cin}, InputIterator{}, std::back_inserter(data));

  std::sort(data.begin(), data.end());

  using OutputIterator = std::ostream_iterator< ahrameev::DataStruct >;
  std::copy(data.begin(), data.end(), OutputIterator{std::cout, "\n"});
}