#include "polygon.hpp"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <functional>
#include <numeric>
#include <iomanip>

namespace em {

double areaIfEven(const Polygon& p) {
  return (p.points.size() % 2 == 0) ? calculateArea(p) : 0.0;
}

void processAreaEven(const std::vector<Polygon>& shapes) {
  const double sum = std::accumulate(
    shapes.cbegin(), shapes.cend(), 0.0,
    std::bind(std::plus<double>(), std::placeholders::_1,
              std::bind(areaIfEven, std::placeholders::_2))
  );
  std::cout << std::fixed << std::setprecision(1) << sum << "\n";
}

}  // namespace em

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

  std::string command;
  while (std::cin >> command) {
    if (command == "AREA") {
      std::string param;
      std::cin >> param;
      if (param == "EVEN") {
        em::processAreaEven(shapes);
      }
    }
  }

  return 0;
}
