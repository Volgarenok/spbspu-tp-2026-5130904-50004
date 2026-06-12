#include "Geometry.h"
#include "IOGuard.h"
#include <iomanip>
#include <limits>
#include <algorithm>
#include <numeric>
#include <iostream>

namespace nepochatova {
  static void cmdArea(const std::vector<Polygon> &v, std::ostream &out, const std::string &param)
  {
    out << std::fixed << std::setprecision(1);

    if (param == "EVEN") {
      double sum = std::accumulate(v.begin(), v.end(), 0.0, AreaSumEven{});
      out << sum;
    } else if (param == "ODD") {
      double sum = std::accumulate(v.begin(), v.end(), 0.0, AreaSumOdd{});
      out << sum;
    } else if (param == "MEAN") {
      if (v.empty()) {
        out << "<INVALID COMMAND>";
        return;
      }
      double sum = std::accumulate(v.begin(), v.end(), 0.0, AreaSumAll{});
      out << (sum / static_cast<double>(v.size()));
    } else {
      try {
        size_t n = std::stoul(param);
        auto fixedAdder = [n](double acc, const Polygon &p) {
          return acc + (p.vertexCount() == n ? p.area() : 0.0);
        };
        out << std::accumulate(v.begin(), v.end(), 0.0, fixedAdder);
      } catch (...) {
        out << "<INVALID COMMAND>";
      }
    }
    out << "\n";
  }

  static void cmdMinMax(const std::vector<Polygon> &v, std::ostream &out,
    const std::string &type, const std::string &param)
  {
    if (v.empty()) {
      out << "<INVALID COMMAND>\n";
      return;
    }

    bool isMax = (type == "MAX");
    out << std::fixed << std::setprecision(1);

    if (param == "AREA") {
      auto cmp = AreaLess{};
      auto it = isMax
                  ? std::max_element(v.begin(), v.end(), cmp)
                  : std::min_element(v.begin(), v.end(), cmp);
      out << it->area();
    } else if (param == "VERTEXES") {
      auto cmp = VertexLess{};
      auto it = isMax
                  ? std::max_element(v.begin(), v.end(), cmp)
                  : std::min_element(v.begin(), v.end(), cmp);
      out << it->vertexCount();
    } else {
      out << "<INVALID COMMAND>";
    }
    out << "\n";
  }

  static void cmdCount(const std::vector<Polygon> &v, std::ostream &out, const std::string &param)
  {
    if (param == "EVEN") {
      out << std::count_if(v.begin(), v.end(), [](const Polygon &p) {
        return p.vertexCount() % 2 == 0;
      });
    } else if (param == "ODD") {
      out << std::count_if(v.begin(), v.end(), [](const Polygon &p) {
        return p.vertexCount() % 2 != 0;
      });
    } else {
      try {
        size_t n = std::stoul(param);
        out << std::count_if(v.begin(), v.end(), [n](const Polygon &p) {
          return p.vertexCount() == n;
        });
      } catch (...) {
        out << "<INVALID COMMAND>";
      }
    }
    out << "\n";
  }

  static void cmdRmEcho(std::vector<Polygon> &v, std::ostream &out, std::istream &in)
  {
    Polygon target;
    if (!(in >> target)) {
      out << "<INVALID COMMAND>\n";
      return;
    }

    size_t removed = 0;
    auto newEnd = v.begin();

    for (auto it = v.begin(); it != v.end();) {
      auto seriesStart = it;

      while (it != v.end() && *it == *seriesStart) ++it;

      if (*seriesStart == target) {
        removed += static_cast<size_t>(it - seriesStart);
      } else {
        newEnd = std::copy(seriesStart, it, newEnd);
      }
    }
    v.erase(newEnd, v.end());
    out << removed << "\n";
  }

  static void cmdInFrame(const std::vector<Polygon> &v, std::ostream &out, std::istream &in) {
    Polygon testPoly;
    if (!(in >> testPoly)) {
      out << "<INVALID COMMAND>\n";
      return;
    }

    if (v.empty()) {
      out << "<FALSE>\n";
      return;
    }

    int minX = std::numeric_limits<int>::max(), maxX = std::numeric_limits<int>::min();
    int minY = std::numeric_limits<int>::max(), maxY = std::numeric_limits<int>::min();

    for (const auto &poly: v) {
      for (const auto &pt: poly.points) {
        minX = std::min(minX, pt.x);
        maxX = std::max(maxX, pt.x);
        minY = std::min(minY, pt.y);
        maxY = std::max(maxY, pt.y);
      }
    }

    bool inside = std::all_of(testPoly.points.begin(), testPoly.points.end(),
      [minX, maxX, minY, maxY](const Point &pt) {
        return pt.x >= minX && pt.x <= maxX && pt.y >= minY && pt.y <= maxY;
    });
    out << (inside ? "<TRUE>" : "<FALSE>") << "\n";
  }


  void processCommands(std::vector<Polygon> &shapes)
  {
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
