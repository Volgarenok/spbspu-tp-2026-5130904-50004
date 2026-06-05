#include "polygon.hpp"

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

int main(int argc, char* argv[])
{
  if (argc < 2) {
    std::cerr << "Error: filename argument required\n"
              << "Usage: " << argv[0] << " filename\n";
    return 1;
  }

  std::ifstream file(argv[1]);
  if (!file.is_open()) {
    std::cerr << "Error: cannot open file: " << argv[1] << "\n";
    return 1;
  }

  std::vector< alberto::Polygon > polys;
  while (!file.eof()) {
    alberto::Polygon poly;
    if (file >> poly) {
      polys.push_back(std::move(poly));
    } else {
      file.clear();
      std::string discard;
      std::getline(file, discard);
    }
  }

  std::string cmd;
  while (std::cin >> cmd) {
    try {
      if (cmd == "AREA") {
        std::string arg;
        if (!(std::cin >> arg)) {
          throw std::invalid_argument("missing argument");
        }
        alberto::cmdArea(std::cout, polys, arg);
      } else if (cmd == "MAX") {
        std::string arg;
        if (!(std::cin >> arg)) {
          throw std::invalid_argument("missing argument");
        }
        alberto::cmdMax(std::cout, polys, arg);
      } else if (cmd == "MIN") {
        std::string arg;
        if (!(std::cin >> arg)) {
          throw std::invalid_argument("missing argument");
        }
        alberto::cmdMin(std::cout, polys, arg);
      } else if (cmd == "COUNT") {
        std::string arg;
        if (!(std::cin >> arg)) {
          throw std::invalid_argument("missing argument");
        }
        alberto::cmdCount(std::cout, polys, arg);
      } else if (cmd == "ECHO") {
        alberto::cmdEcho(std::cout, polys, std::cin);
      } else if (cmd == "RMECHO") {
        alberto::cmdRmecho(std::cout, polys, std::cin);
      } else {
        throw std::invalid_argument("unknown command");
      }
    } catch (const std::exception&) {
      std::cout << "<INVALID COMMAND>\n";
      std::string discard;
      std::getline(std::cin, discard);
    }
  }
  return 0;
}
