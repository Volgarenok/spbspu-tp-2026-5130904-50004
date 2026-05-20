#include "data-struct.hpp"

#include <vector>
#include <iterator>
#include <algorithm>

int main()
{
  using ali::DataStruct;

  std::vector< DataStruct > data;

  while (!std::cin.eof())
  {
    DataStruct temp;

    if (std::cin >> temp)
    {
      data.push_back(temp);
    }
    else
    {
      std::cin.clear();

      std::string skip;
      std::getline(std::cin, skip);
    }
  }

  std::sort(data.begin(), data.end());

  std::copy(
    data.begin(),
    data.end(),
    std::ostream_iterator< DataStruct >(std::cout, "\n"));

  return 0;
}
