#include "polygon.hpp"
#include "bounding_box.hpp"
#include "commands.hpp"

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

namespace
{

  void printUsage(const char* programName)
  {
    std::cerr << "Usage: " << programName << " <filename>\n";
  }

  void exitWithError(const std::string& message)
  {
    std::cerr << message << '\n';
    std::exit(1);
  }

  std::ifstream openInputFile(const std::string& filename)
  {
    std::ifstream file(filename);
    if (!file)
    {
      exitWithError("Cannot open file: " + filename);
    }
    return file;
  }

  bool tryParsePolygonFromLine(const std::string& line, ahrameev::Polygon& poly)
  {
    if (line.empty())
    {
      return false;
    }
    std::istringstream lineStream(line);
    if (!(lineStream >> poly))
    {
      return false;
    }
    std::string tail;
    if (lineStream >> tail)
    {
      return false;
    }
    return true;
  }

  std::vector< ahrameev::Polygon > loadPolygonsFromFile(const std::string& filename)
  {
    std::ifstream file = openInputFile(filename);
    std::vector< ahrameev::Polygon > polygons;
    std::string line;
    while (std::getline(file, line))
    {
      ahrameev::Polygon poly{};
      if (tryParsePolygonFromLine(line, poly))
      {
        polygons.push_back(std::move(poly));
      }
    }
    return polygons;
  }

}

int main(int argc, char* argv[])
{
  if (argc != 2)
  {
    printUsage(argv[0]);
    return 1;
  }
  std::vector< ahrameev::Polygon > polygons = loadPolygonsFromFile(argv[1]);
  ahrameev::BoundingBox globalBox = ahrameev::computeGlobalBoundingBox(polygons);
}