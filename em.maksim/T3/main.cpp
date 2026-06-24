#include "polygon.hpp"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

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

  std::vector<em::Polygon> shapes;
  em::Polygon poly;
  while (file >> poly) {
    shapes.push_back(poly);
  }

  return 0;
}
