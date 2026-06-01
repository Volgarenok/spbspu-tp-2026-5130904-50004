#ifndef COMMAND_H
#define COMMAND_H

#include "Polygon.h"
#include <vector>
#include <iosfwd>

namespace vasilenko
{
  void commandArea(const std::vector<Polygon>& polygons, std::istream& in, std::ostream& out);
  void commandMax(const std::vector<Polygon>& polygons, std::istream& in, std::ostream& out);
  void commandMin(const std::vector<Polygon>& polygons, std::istream& in, std::ostream& out);
  void commandCount(const std::vector<Polygon>& polygons, std::istream& in, std::ostream& out);

  void commandRmEcho(std::vector<Polygon>& polygons, std::istream& in, std::ostream& out);
  void commandSame(const std::vector<Polygon>& polygons, std::istream& in, std::ostream& out);
}

#endif
