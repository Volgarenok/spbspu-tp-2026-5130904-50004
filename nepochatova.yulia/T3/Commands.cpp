#include "Geometry.h"
#include "IOGuard.h"
#include <iomanip>
#include <limits>
#include <algorithm>
#include <numeric>
#include <iostream>

namespace nepochatova {
  void cmdArea(const std::vector<Polygon> &v, std::ostream &out, const std::string &param);

  void cmdMinMax(const std::vector<Polygon> &v, std::ostream &out, const std::string &type, const std::string &param);

  void cmdCount(const std::vector<Polygon> &v, std::ostream &out, const std::string &param);

  void cmdRmEcho(std::vector<Polygon> &v, std::ostream &out, std::istream &in);

  void cmdInFrame(const std::vector<Polygon> &v, std::ostream &out, std::istream &in);

  void processCommands(std::vector<Polygon> &shapes) {
    std::string cmd, param;

    while (std::cin >> cmd) {
      if (cmd == "AREA") {
        if (std::cin >> param) {
          cmdArea(shapes, std::cout, param);
        } else {
          std::cout << "<INVALID COMMAND>\n";
        }
      } else if (cmd == "MAX" || cmd == "MIN") {
        if (std::cin >> param) {
          cmdMinMax(shapes, std::cout, cmd, param);
        } else {
          std::cout << "<INVALID COMMAND>\n";
        }
      } else if (cmd == "COUNT") {
        if (std::cin >> param) {
          cmdCount(shapes, std::cout, param);
        } else {
          std::cout << "<INVALID COMMAND>\n";
        }
      } else if (cmd == "RMECHO") {
        cmdRmEcho(shapes, std::cout, std::cin);
      } else if (cmd == "INFRAME") {
        cmdInFrame(shapes, std::cout, std::cin);
      } else {
        std::cout << "<INVALID COMMAND>\n";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      }
    }
  }
}