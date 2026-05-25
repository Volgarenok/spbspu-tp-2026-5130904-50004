#include "commands.hpp"
#include "geometry.hpp"

#include <fstream>
#include <iostream>
#include <iterator>
#include <vector>
#include <algorithm>

int main(int argc, char* argv[])
{
  if (argc != 2)
  {
    std::cerr << "Invalid command line\n";
    return 1;
  }

  std::ifstream input(argv[1]);

  if (!input)
  {
    std::cerr << "Cannot open file\n";
    return 1;
  }

  aydogan::PolygonList polygons;

  std::copy(
    std::istream_iterator< aydogan::Polygon >(input),
    std::istream_iterator< aydogan::Polygon >(),
    std::back_inserter(polygons)
  );

  aydogan::runCommands(polygons, std::cin, std::cout);

  return 0;
}
