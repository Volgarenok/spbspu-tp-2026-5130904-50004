#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include "Geometry.hpp"
#include <vector>
#include <iosfwd>

namespace pozdeev
{
  void executeArea(const std::vector< Polygon >& polygons, std::istream& in, std::ostream& out);
  void executeMax(const std::vector< Polygon >& polygons, std::istream& in, std::ostream& out);
  void executeMin(const std::vector< Polygon >& polygons, std::istream& in, std::ostream& out);
  void executeCount(const std::vector< Polygon >& polygons, std::istream& in, std::ostream& out);
  void executeInframe(const std::vector< Polygon >& polygons, std::istream& in, std::ostream& out);
  void executeSame(const std::vector< Polygon >& polygons, std::istream& in, std::ostream& out);
}

#endif
