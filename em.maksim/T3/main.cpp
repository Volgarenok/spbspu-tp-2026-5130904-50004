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

double areaIfOdd(const Polygon& p) {
  return (p.points.size() % 2 != 0) ? calculateArea(p) : 0.0;
}

void processAreaEven(const std::vector<Polygon>& shapes) {
  const double sum = std::accumulate(
    shapes.cbegin(), shapes.cend(), 0.0,
    std::bind(std::plus<double>(), std::placeholders::_1,
              std::bind(areaIfEven, std::placeholders::_2))
  );
  std::cout << std::fixed << std::setprecision(1) << sum << "\n";
}

void processAreaOdd(const std::vector<Polygon>& shapes) {
  const double sum = std::accumulate(
    shapes.cbegin(), shapes.cend(), 0.0,
    std::bind(std::plus<double>(), std::placeholders::_1,
              std::bind(areaIfOdd, std::placeholders::_2))
  );
  std::cout << std::fixed << std::setprecision(1) << sum << "\n";
}

void processAreaMean(const std::vector<Polygon>& shapes) {
  if (shapes.empty()) {
    std::cout << "<INVALID COMMAND>\n";
    return;
  }
  const double total = std::accumulate(
    shapes.cbegin(), shapes.cend(), 0.0,
    std::bind(std::plus<double>(), std::placeholders::_1,
              std::bind(calculateArea, std::placeholders::_2))
  );
  std::cout << std::fixed << std::setprecision(1)
            << (total / shapes.size()) << "\n";
}

struct AreaAccumulator {
  size_t target;
  explicit AreaAccumulator(size_t t): target(t) {}
  double operator()(double acc, const Polygon& p) const {
    return acc + ((p.points.size() == target) ? calculateArea(p) : 0.0);
  }
};

void processAreaVertexes(const std::vector<Polygon>& shapes, size_t num) {
  const double sum = std::accumulate(
    shapes.cbegin(), shapes.cend(), 0.0, AreaAccumulator(num)
  );
  std::cout << std::fixed << std::setprecision(1) << sum << "\n";
}

struct CompareArea {
  bool operator()(const Polygon& a, const Polygon& b) const {
    return calculateArea(a) < calculateArea(b);
  }
};

void processMaxArea(const std::vector<Polygon>& shapes) {
  if (shapes.empty()) {
    std::cout << "<INVALID COMMAND>\n";
    return;
  }
  const auto it = std::max_element(
    shapes.cbegin(), shapes.cend(), CompareArea{}
  );
  std::cout << std::fixed << std::setprecision(1)
            << calculateArea(*it) << "\n";
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
      } else if (param == "ODD") {
        em::processAreaOdd(shapes);
      } else if (param == "MEAN") {
        em::processAreaMean(shapes);
      } else {
        try {
          const size_t num = std::stoul(param);
          em::processAreaVertexes(shapes, num);
        } catch (...) {
          std::cout << "<INVALID COMMAND>\n";
        }
      }
    } else if (command == "MAX") {
      std::string param;
      std::cin >> param;
      if (param == "AREA") {
        em::processMaxArea(shapes);
      }
    }
  }

  return 0;
}
