#include "Commands.hpp"
#include "Formatters.hpp"
#include <iomanip>
#include <string>
#include <numeric>
#include <algorithm>
#include <functional>
#include <stdexcept>
#include <cctype>

namespace
{
  void checkEmptyLine(std::istream& in)
  {
    char c;
    while (in.get(c))
    {
      if (c == '\n')
      {
        in.unget();
        break;
      }
      if (!std::isspace(c))
      {
        in.setstate(std::ios::failbit);
        throw std::invalid_argument("Trailing garbage");
      }
    }
  }
}

namespace pozdeev
{
  void executeArea(const std::vector< Polygon >& polygons, std::istream& in, std::ostream& out)
  {
    std::string arg;
    in >> arg;
    checkEmptyLine(in);

    std::vector< double > areas(polygons.size());

    if (arg == "EVEN")
    {
      std::transform(polygons.begin(), polygons.end(), areas.begin(), getAreaIfEven);
      double sum = std::accumulate(areas.begin(), areas.end(), 0.0);
      IOGuard guard(out);
      out << std::fixed << std::setprecision(1) << sum << '\n';
    }
    else if (arg == "ODD")
    {
      std::transform(polygons.begin(), polygons.end(), areas.begin(), getAreaIfOdd);
      double sum = std::accumulate(areas.begin(), areas.end(), 0.0);
      IOGuard guard(out);
      out << std::fixed << std::setprecision(1) << sum << '\n';
    }
    else if (arg == "MEAN")
    {
      if (polygons.empty())
      {
        throw std::invalid_argument("Empty polygons");
      }
      std::transform(polygons.begin(), polygons.end(), areas.begin(), getArea);
      double sum = std::accumulate(areas.begin(), areas.end(), 0.0);
      IOGuard guard(out);
      out << std::fixed << std::setprecision(1) << sum / polygons.size() << '\n';
    }
    else if (std::isdigit(arg[0]))
    {
      size_t vertexes = std::stoull(arg);
      if (vertexes < 3)
      {
        throw std::invalid_argument("Invalid vertexes count");
      }
      using namespace std::placeholders;
      std::transform(polygons.begin(), polygons.end(), areas.begin(), std::bind(getAreaIfNum, _1, vertexes));
      double sum = std::accumulate(areas.begin(), areas.end(), 0.0);
      IOGuard guard(out);
      out << std::fixed << std::setprecision(1) << sum << '\n';
    }
    else
    {
      throw std::invalid_argument("Invalid argument");
    }
  }

  void executeMax(const std::vector< Polygon >& polygons, std::istream& in, std::ostream& out)
  {
    if (polygons.empty())
    {
      throw std::invalid_argument("Empty polygons");
    }
    std::string arg;
    in >> arg;
    checkEmptyLine(in);

    if (arg == "AREA")
    {
      auto it = std::max_element(polygons.begin(), polygons.end(), compareArea);
      IOGuard guard(out);
      out << std::fixed << std::setprecision(1) << getArea(*it) << '\n';
    }
    else if (arg == "VERTEXES")
    {
      auto it = std::max_element(polygons.begin(), polygons.end(), compareVertexes);
      out << it->points.size() << '\n';
    }
    else
    {
      throw std::invalid_argument("Invalid argument");
    }
  }

  void executeMin(const std::vector< Polygon >& polygons, std::istream& in, std::ostream& out)
  {
    if (polygons.empty())
    {
      throw std::invalid_argument("Empty polygons");
    }
    std::string arg;
    in >> arg;
    checkEmptyLine(in);

    if (arg == "AREA")
    {
      auto it = std::min_element(polygons.begin(), polygons.end(), compareArea);
      IOGuard guard(out);
      out << std::fixed << std::setprecision(1) << getArea(*it) << '\n';
    }
    else if (arg == "VERTEXES")
    {
      auto it = std::min_element(polygons.begin(), polygons.end(), compareVertexes);
      out << it->points.size() << '\n';
    }
    else
    {
      throw std::invalid_argument("Invalid argument");
    }
  }

  void executeCount(const std::vector< Polygon >& polygons, std::istream& in, std::ostream& out)
  {
    std::string arg;
    in >> arg;
    checkEmptyLine(in);

    if (arg == "EVEN")
    {
      out << std::count_if(polygons.begin(), polygons.end(), isEven) << '\n';
    }
    else if (arg == "ODD")
    {
      out << std::count_if(polygons.begin(), polygons.end(), isOdd) << '\n';
    }
    else if (std::isdigit(arg[0]))
    {
      size_t vertexes = std::stoull(arg);
      if (vertexes < 3)
      {
        throw std::invalid_argument("Invalid vertexes count");
      }
      using namespace std::placeholders;
      out << std::count_if(polygons.begin(), polygons.end(), std::bind(hasVertexes, _1, vertexes)) << '\n';
    }
    else
    {
      throw std::invalid_argument("Invalid argument");
    }
  }

  void executeInframe(const std::vector< Polygon >& polygons, std::istream& in, std::ostream& out)
  {
    Polygon target;
    if (!(in >> target))
    {
      throw std::invalid_argument("Invalid polygon");
    }
    checkEmptyLine(in);

    if (polygons.empty())
    {
      out << "<FALSE>\n";
      return;
    }
    int minX = getMinX(*std::min_element(polygons.begin(), polygons.end(), compareMinX));
    int maxX = getMaxX(*std::max_element(polygons.begin(), polygons.end(), compareMaxX));
    int minY = getMinY(*std::min_element(polygons.begin(), polygons.end(), compareMinY));
    int maxY = getMaxY(*std::max_element(polygons.begin(), polygons.end(), compareMaxY));

    int tMinX = getMinX(target);
    int tMaxX = getMaxX(target);
    int tMinY = getMinY(target);
    int tMaxY = getMaxY(target);

    if (tMinX >= minX && tMaxX <= maxX && tMinY >= minY && tMaxY <= maxY)
    {
      out << "<TRUE>\n";
    }
    else
    {
      out << "<FALSE>\n";
    }
  }

  void executeSame(const std::vector< Polygon >& polygons, std::istream& in, std::ostream& out)
  {
    Polygon target;
    if (!(in >> target))
    {
      throw std::invalid_argument("Invalid polygon");
    }
    checkEmptyLine(in);

    using namespace std::placeholders;
    out << std::count_if(polygons.begin(), polygons.end(), std::bind(isSame, _1, target)) << '\n';
  }
}
