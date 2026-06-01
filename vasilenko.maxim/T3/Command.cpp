#include "Command.h"
#include "Functions.h"
#include <numeric>
#include <algorithm>
#include <iomanip>
#include <string>
#include <stdexcept>

namespace vasilenko
{
  void commandArea(const std::vector<Polygon>& polygons, std::istream& in, std::ostream& out)
  {
    std::string sub;
    in >> sub;

    std::vector<double> areas(polygons.size());
    if (sub == "EVEN") {
      std::transform(polygons.begin(), polygons.end(), areas.begin(), std::bind(areaIf, std::placeholders::_1, isEven));
      out << std::fixed << std::setprecision(1) << std::accumulate(areas.begin(), areas.end(), 0.0) << "\n";
    } else if (sub == "ODD") {
      std::transform(polygons.begin(), polygons.end(), areas.begin(), std::bind(areaIf, std::placeholders::_1, isOdd));
      out << std::fixed << std::setprecision(1) << std::accumulate(areas.begin(), areas.end(), 0.0) << "\n";
    } else if (sub == "MEAN") {
      if (polygons.empty()) {
        throw std::runtime_error("Empty collection");
      }
      std::transform(polygons.begin(), polygons.end(), areas.begin(), getArea);
      double sum = std::accumulate(areas.begin(), areas.end(), 0.0);
      out << std::fixed << std::setprecision(1) << sum / static_cast<double>(polygons.size()) << "\n";
    } else {
      size_t num = std::stoull(sub);
      std::transform(polygons.begin(), polygons.end(), areas.begin(), std::bind(areaIf, std::placeholders::_1, std::bind(hasVertices, std::placeholders::_1, num)));
      out << std::fixed << std::setprecision(1) << std::accumulate(areas.begin(), areas.end(), 0.0) << "\n";
    }
  }

  void commandMax(const std::vector<Polygon>& polygons, std::istream& in, std::ostream& out)
  {
    if (polygons.empty()) {
      throw std::runtime_error("Empty collection");
    }
    std::string sub;
    in >> sub;

    if (sub == "AREA") {
      auto it = std::max_element(polygons.begin(), polygons.end(), compareArea);
      out << std::fixed << std::setprecision(1) << getArea(*it) << "\n";
    } else if (sub == "VERTEXES") {
      auto it = std::max_element(polygons.begin(), polygons.end(), compareVertices);
      out << it->points.size() << "\n";
    } else {
      throw std::runtime_error("Invalid subcommand");
    }
  }

  void commandMin(const std::vector<Polygon>& polygons, std::istream& in, std::ostream& out)
  {
    if (polygons.empty()) {
      throw std::runtime_error("Empty collection");
    }
    std::string sub;
    in >> sub;

    if (sub == "AREA") {
      auto it = std::min_element(polygons.begin(), polygons.end(), compareArea);
      out << std::fixed << std::setprecision(1) << getArea(*it) << "\n";
    } else if (sub == "VERTEXES") {
      auto it = std::min_element(polygons.begin(), polygons.end(), compareVertices);
      out << it->points.size() << "\n";
    } else {
      throw std::runtime_error("Invalid subcommand");
    }
  }

  void commandCount(const std::vector<Polygon>& polygons, std::istream& in, std::ostream& out)
  {
    std::string sub;
    in >> sub;

    if (sub == "EVEN") {
      out << std::count_if(polygons.begin(), polygons.end(), isEven) << "\n";
    } else if (sub == "ODD") {
      out << std::count_if(polygons.begin(), polygons.end(), isOdd) << "\n";
    } else {
      size_t num = std::stoull(sub);
      out << std::count_if(polygons.begin(), polygons.end(), std::bind(hasVertices, std::placeholders::_1, num)) << "\n";
    }
  }

  void commandRmEcho(std::vector<Polygon>& polygons, std::istream& in, std::ostream& out)
  {
    Polygon target;
    if (!(in >> target)) {
      throw std::runtime_error("Invalid polygon");
    }
    size_t initialSize = polygons.size();
    auto it = std::unique(polygons.begin(), polygons.end(), std::bind(isTargetDuplicate, std::placeholders::_1, std::placeholders::_2, target));
    polygons.erase(it, polygons.end());
    out << initialSize - polygons.size() << "\n";
  }

  void commandSame(const std::vector<Polygon>& polygons, std::istream& in, std::ostream& out)
  {
    Polygon target;
    if (!(in >> target)) {
      throw std::runtime_error("Invalid polygon");
    }
    out << std::count_if(polygons.begin(), polygons.end(), std::bind(isSame, std::placeholders::_1, target)) << "\n";
  }
}
