#include "Geometry.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <iterator>


int main(int argc, char* argv[]) {
  if (argc != 2) {
    std::cerr << "Usage: " << argv[0] << " <filename>\n";
    return 1;
  }

  std::ifstream file(argv[1]);
  if (!file) {
    std::cerr << "Cannot open file: " << argv[1] << "\n";
    return 1;
  }

  std::vector<nepochatova::Polygon> shapes;
  using PolyIt = std::istream_iterator<nepochatova::Polygon>;
  std::copy(PolyIt(file), PolyIt{}, std::back_inserter(shapes));
  file.close();

  nepochatova::processCommands(shapes);

  return 0;
}
