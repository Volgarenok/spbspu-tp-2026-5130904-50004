#include "geometry.hpp"

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <iterator>

int main(int argc, char * argv[])
{
  if (argc != 2)
  {
    std::cerr << "error\n";
    return 1;
  }

  std::ifstream input(argv[1]);

  if (!input)
  {
    std::cerr << "error\n";
    return 1;
  }

  std::vector< ali::Polygon > polygons;

  while (!input.eof())
  {
    ali::Polygon polygon;

    if (input >> polygon)
    {
      polygons.push_back(polygon);
    }
    else
    {
      input.clear();

      std::string skip;
      std::getline(input, skip);
    }
  }

  std::string command;

  while (std::cin >> command)
  {
    if (command == "RECTS")
    {
      std::size_t count =
        std::count_if(
          polygons.begin(),
          polygons.end(),
          ali::isRectangle);

      std::cout << count << '\n';
    }
    else if (command == "ECHO")
    {
      ali::Polygon target;

      if (!(std::cin >> target))
      {
        std::cout << "<INVALID COMMAND>\n";

        std::cin.clear();

        std::string skip;
        std::getline(std::cin, skip);

        continue;
      }

      std::size_t added = 0;
      std::vector< ali::Polygon > result;

      for (const auto & polygon: polygons)
      {
        result.push_back(polygon);

        if (polygon == target)
        {
          result.push_back(polygon);
          ++added;
        }
      }

      polygons = result;

      std::cout << added << '\n';
    }
    else
    {
      std::cout << "<INVALID COMMAND>\n";
    }
  }

  return 0;
}
