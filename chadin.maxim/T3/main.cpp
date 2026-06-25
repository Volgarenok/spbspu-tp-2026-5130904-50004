#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>
#include <string>
#include <algorithm>
#include <sstream>
#include "Polygon.hpp"
#include "Commands.hpp"

namespace chadin {
  namespace detail {

    struct LineReader
    {
      std::string line;
      operator std::string() const { return line; }
      friend std::istream& operator>>(std::istream& in, LineReader& lr)
      {
        return std::getline(in, lr.line);
      }
    };

    struct parse_polygon
    {
      Polygon operator()(const std::string& str) const
      {
        std::istringstream iss(str);
        Polygon p;
        if (iss >> p) {
          return p;
        }
        return {};
      }
    };
