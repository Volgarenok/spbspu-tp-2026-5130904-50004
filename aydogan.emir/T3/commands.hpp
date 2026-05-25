#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include "geometry.hpp"

#include <iosfwd>
#include <string>
#include <vector>

namespace aydogan
{
  using PolygonList = std::vector< Polygon >;

  void runCommands(const PolygonList& polygons, std::istream& input, std::ostream& output);

  void printAreaEven(const PolygonList& polygons, std::ostream& output);
  void printAreaOdd(const PolygonList& polygons, std::ostream& output);
  void printAreaMean(const PolygonList& polygons, std::ostream& output);
  void printAreaVertexCount(const PolygonList& polygons, std::size_t count, std::ostream& output);

  void printMaxArea(const PolygonList& polygons, std::ostream& output);
  void printMaxVertexes(const PolygonList& polygons, std::ostream& output);
  void printMinArea(const PolygonList& polygons, std::ostream& output);
  void printMinVertexes(const PolygonList& polygons, std::ostream& output);

  void printCountEven(const PolygonList& polygons, std::ostream& output);
  void printCountOdd(const PolygonList& polygons, std::ostream& output);
  void printCountVertexCount(const PolygonList& polygons, std::size_t count, std::ostream& output);

  void printPerms(const PolygonList& polygons, const Polygon& polygon, std::ostream& output);
  void printRightShapes(const PolygonList& polygons, std::ostream& output);
}

#endif
