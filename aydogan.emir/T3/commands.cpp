#include "commands.hpp"

#include <algorithm>
#include <functional>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <numeric>
#include <sstream>
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
