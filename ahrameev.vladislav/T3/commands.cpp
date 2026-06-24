#include "commands.hpp"

#include <algorithm>
#include <functional>
#include <iostream>
#include <string>

namespace ahrameev
{

  namespace
  {

    void printInvalidCommand()
    {
      std::cout << "<INVALID COMMAND>\n";
    }

    void printIntResult(int value)
    {
      std::cout << value << '\n';
    }

    void printBoolResult(bool value)
    {
      if (value)
      {
        std::cout << "<TRUE>\n";
      }
      else
      {
        std::cout << "<FALSE>\n";
      }
    }

    bool hasTrailingContent(std::istringstream& stream)
    {
      std::string tail;
      if (stream >> tail)
      {
        return true;
      }
      return false;
    }

    bool tryReadPolygon(std::istringstream& stream, Polygon& poly)
    {
      if (!(stream >> poly))
      {
        return false;
      }
      if (hasTrailingContent(stream))
      {
        return false;
      }
      return true;
    }

    int countPermutations(
      const std::vector< Polygon >& polygons,
      const Polygon& sample)
    {
      return std::count_if(
        polygons.cbegin(),
        polygons.cend(),
        std::bind(isPermutation, sample, std::placeholders::_1)
      );
    }

    bool isBoxValid(const BoundingBox& box)
    {
      return box.isValid;
    }

    bool checkPolygonInsideBox(
      const BoundingBox& box,
      const Polygon& poly)
    {
      return isPolygonInsideBox(box, poly);
    }

  }

  void handlePermsCommand(
    const std::vector< Polygon >& polygons,
    std::istringstream& cmdStream)
  {
    Polygon sample{};
    if (!tryReadPolygon(cmdStream, sample))
    {
      printInvalidCommand();
      return;
    }
    int count = countPermutations(polygons, sample);
    printIntResult(count);
  }

  void handleInFrameCommand(
    const BoundingBox& globalBox,
    std::istringstream& cmdStream)
  {
    Polygon testPoly{};
    if (!tryReadPolygon(cmdStream, testPoly))
    {
      printInvalidCommand();
      return;
    }
    if (!isBoxValid(globalBox))
    {
      printBoolResult(false);
      return;
    }
    bool inside = checkPolygonInsideBox(globalBox, testPoly);
    printBoolResult(inside);
  }

}