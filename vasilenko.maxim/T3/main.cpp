#include "Polygon.h"
#include "Command.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <functional>
#include <limits>

int main(int argc, char* argv[])
{
  if (argc != 2) {
    std::cerr << "Usage: ./lab filename\n";
    return 1;
  }

  std::ifstream file(argv[1]);
  if (!file) {
    std::cerr << "Cannot open file\n";
    return 1;
  }

  std::vector<vasilenko::Polygon> polygons;
  while (!file.eof()) {
    vasilenko::Polygon p;
    if (file >> p) {
      polygons.push_back(p);
    } else if (!file.eof()) {
      file.clear();
      file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
  }

  std::map<std::string, std::function<void(std::istream&, std::ostream&)>> commands;

  commands["AREA"] = std::bind(vasilenko::commandArea, std::cref(polygons), std::placeholders::_1, std::placeholders::_2);
  commands["MAX"] = std::bind(vasilenko::commandMax, std::cref(polygons), std::placeholders::_1, std::placeholders::_2);
  commands["MIN"] = std::bind(vasilenko::commandMin, std::cref(polygons), std::placeholders::_1, std::placeholders::_2);
  commands["COUNT"] = std::bind(vasilenko::commandCount, std::cref(polygons), std::placeholders::_1, std::placeholders::_2);
  commands["RMECHO"] = std::bind(vasilenko::commandRmEcho, std::ref(polygons), std::placeholders::_1, std::placeholders::_2);
  commands["SAME"] = std::bind(vasilenko::commandSame, std::cref(polygons), std::placeholders::_1, std::placeholders::_2);

  std::string cmd;
  while (std::cin >> cmd) {
    auto it = commands.find(cmd);
    if (it != commands.end()) {
      try {
        it->second(std::cin, std::cout);
      } catch (...) {
        std::cout << "<INVALID COMMAND>\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      }
    } else {
      std::cout << "<INVALID COMMAND>\n";
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
  }

  return 0;
}
