#include "commands.hpp"

#include <algorithm>
#include <functional>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <numeric>
#include <sstream>
#include <string>
#include <vector>

namespace
{
  struct AreaGetter
  {
    double operator()(const aydogan::Polygon& polygon) const
    {
      return aydogan::getArea(polygon);
    }
  };

  struct VertexCountGetter
  {
    std::size_t operator()(const aydogan::Polygon& polygon) const
    {
      return aydogan::getVertexCount(polygon);
    }
  };

  struct HasVertexCount
  {
    std::size_t count;

    bool operator()(const aydogan::Polygon& polygon) const
    {
      return aydogan::hasVertexCount(polygon, count);
    }
  };

  struct IsPermutation
  {
    const aydogan::Polygon& polygon;

    bool operator()(const aydogan::Polygon& current) const
    {
      return aydogan::isPermutationOf(current, polygon);
    }
  };

  struct AreaLess
  {
    bool operator()(const aydogan::Polygon& left, const aydogan::Polygon& right) const
    {
      return aydogan::getArea(left) < aydogan::getArea(right);
    }
  };

  struct VertexCountLess
  {
    bool operator()(const aydogan::Polygon& left, const aydogan::Polygon& right) const
    {
      return aydogan::getVertexCount(left) < aydogan::getVertexCount(right);
    }
  };

  struct Line
  {
    std::string text;
  };

  std::istream& operator>>(std::istream& input, Line& line)
  {
    std::istream::sentry sentry(input);

    if (!sentry)
    {
      return input;
    }

    std::getline(input, line.text);

    if (line.text.empty() && !input)
    {
      input.setstate(std::ios::failbit);
    }

    return input;
  }

  void printInvalid(std::ostream& output)
  {
    output << "<INVALID COMMAND>\n";
  }

  void printDouble(double value, std::ostream& output)
  {
    output << std::fixed << std::setprecision(1) << value << "\n";
  }

  double getAreaSum(const aydogan::PolygonList& polygons)
  {
    std::vector< double > areas(polygons.size());

    std::transform(
      polygons.begin(),
      polygons.end(),
      areas.begin(),
      AreaGetter{}
    );

    return std::accumulate(areas.begin(), areas.end(), 0.0);
  }

  template< class Predicate >
  double getFilteredAreaSum(const aydogan::PolygonList& polygons, Predicate predicate)
  {
    aydogan::PolygonList filtered;

    std::copy_if(
      polygons.begin(),
      polygons.end(),
      std::back_inserter(filtered),
      predicate
    );

    return getAreaSum(filtered);
  }

  void requireNotEmpty(const aydogan::PolygonList& polygons, std::ostream& output, bool& ok)
  {
    if (polygons.empty())
    {
      printInvalid(output);
      ok = false;
    }
    else
    {
      ok = true;
    }
  }

  struct CommandExecutor
  {
    const aydogan::PolygonList& polygons;

    std::string operator()(const Line& line) const
    {
      std::istringstream input(line.text);
      std::ostringstream output;

      std::string command;
      input >> command;

      if (command == "AREA")
      {
        std::string argument;
        input >> argument;

        if (argument == "EVEN")
        {
          aydogan::printAreaEven(polygons, output);
        }
        else if (argument == "ODD")
        {
          aydogan::printAreaOdd(polygons, output);
        }
        else if (argument == "MEAN")
        {
          aydogan::printAreaMean(polygons, output);
        }
        else
        {
          std::istringstream numberInput(argument);
          std::size_t count = 0;
          numberInput >> count;

          if (numberInput && numberInput.eof())
          {
            aydogan::printAreaVertexCount(polygons, count, output);
          }
          else
          {
            printInvalid(output);
          }
        }
      }
      else if (command == "MAX")
      {
        std::string argument;
        input >> argument;

        if (argument == "AREA")
        {
          aydogan::printMaxArea(polygons, output);
        }
        else if (argument == "VERTEXES")
        {
          aydogan::printMaxVertexes(polygons, output);
        }
        else
        {
          printInvalid(output);
        }
      }
      else if (command == "MIN")
      {
        std::string argument;
        input >> argument;

        if (argument == "AREA")
        {
          aydogan::printMinArea(polygons, output);
        }
        else if (argument == "VERTEXES")
        {
          aydogan::printMinVertexes(polygons, output);
        }
        else
        {
          printInvalid(output);
        }
      }
      else if (command == "COUNT")
      {
        std::string argument;
        input >> argument;

        if (argument == "EVEN")
        {
          aydogan::printCountEven(polygons, output);
        }
        else if (argument == "ODD")
        {
          aydogan::printCountOdd(polygons, output);
        }
        else
        {
          std::istringstream numberInput(argument);
          std::size_t count = 0;
          numberInput >> count;

          if (numberInput && numberInput.eof())
          {
            aydogan::printCountVertexCount(polygons, count, output);
          }
          else
          {
            printInvalid(output);
          }
        }
      }
      else if (command == "PERMS")
      {
        aydogan::Polygon polygon;
        input >> polygon;

        if (input)
        {
          aydogan::printPerms(polygons, polygon, output);
        }
        else
        {
          printInvalid(output);
        }
      }
      else if (command == "RIGHTSHAPES")
      {
        aydogan::printRightShapes(polygons, output);
      }
      else
      {
        printInvalid(output);
      }

      return output.str();
    }
  };
}

void aydogan::printAreaEven(const PolygonList& polygons, std::ostream& output)
{
  printDouble(getFilteredAreaSum(polygons, hasEvenVertexCount), output);
}

void aydogan::printAreaOdd(const PolygonList& polygons, std::ostream& output)
{
  printDouble(getFilteredAreaSum(polygons, hasOddVertexCount), output);
}

void aydogan::printAreaMean(const PolygonList& polygons, std::ostream& output)
{
  if (polygons.empty())
  {
    printInvalid(output);
    return;
  }

  printDouble(getAreaSum(polygons) / polygons.size(), output);
}

void aydogan::printAreaVertexCount(
  const PolygonList& polygons,
  std::size_t count,
  std::ostream& output
)
{
  if (count < 3)
  {
    printInvalid(output);
    return;
  }

  printDouble(getFilteredAreaSum(polygons, HasVertexCount{ count }), output);
}

void aydogan::printMaxArea(const PolygonList& polygons, std::ostream& output)
{
  bool ok = false;
  requireNotEmpty(polygons, output, ok);

  if (!ok)
  {
    return;
  }

  auto result = std::max_element(polygons.begin(), polygons.end(), AreaLess{});
  printDouble(getArea(*result), output);
}

void aydogan::printMaxVertexes(const PolygonList& polygons, std::ostream& output)
{
  bool ok = false;
  requireNotEmpty(polygons, output, ok);

  if (!ok)
  {
    return;
  }

  auto result = std::max_element(polygons.begin(), polygons.end(), VertexCountLess{});
  output << getVertexCount(*result) << "\n";
}

void aydogan::printMinArea(const PolygonList& polygons, std::ostream& output)
{
  bool ok = false;
  requireNotEmpty(polygons, output, ok);

  if (!ok)
  {
    return;
  }

  auto result = std::min_element(polygons.begin(), polygons.end(), AreaLess{});
  printDouble(getArea(*result), output);
}

void aydogan::printMinVertexes(const PolygonList& polygons, std::ostream& output)
{
  bool ok = false;
  requireNotEmpty(polygons, output, ok);

  if (!ok)
  {
    return;
  }

  auto result = std::min_element(polygons.begin(), polygons.end(), VertexCountLess{});
  output << getVertexCount(*result) << "\n";
}

void aydogan::printCountEven(const PolygonList& polygons, std::ostream& output)
{
  output << std::count_if(polygons.begin(), polygons.end(), hasEvenVertexCount) << "\n";
}

void aydogan::printCountOdd(const PolygonList& polygons, std::ostream& output)
{
  output << std::count_if(polygons.begin(), polygons.end(), hasOddVertexCount) << "\n";
}

void aydogan::printCountVertexCount(
  const PolygonList& polygons,
  std::size_t count,
  std::ostream& output
)
{
  if (count < 3)
  {
    printInvalid(output);
    return;
  }

  output << std::count_if(polygons.begin(), polygons.end(), HasVertexCount{ count }) << "\n";
}

void aydogan::printPerms(
  const PolygonList& polygons,
  const Polygon& polygon,
  std::ostream& output
)
{
  output << std::count_if(polygons.begin(), polygons.end(), IsPermutation{ polygon }) << "\n";
}

void aydogan::printRightShapes(const PolygonList& polygons, std::ostream& output)
{
  output << std::count_if(polygons.begin(), polygons.end(), hasRightAngle) << "\n";
}

void aydogan::runCommands(
  const PolygonList& polygons,
  std::istream& input,
  std::ostream& output
)
{
  std::vector< Line > lines;

  std::copy(
    std::istream_iterator< Line >(input),
    std::istream_iterator< Line >(),
    std::back_inserter(lines)
  );

  std::transform(
    lines.begin(),
    lines.end(),
    std::ostream_iterator< std::string >(output, ""),
    CommandExecutor{ polygons }
  );
}
