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

  bool readCommandName(std::istringstream& stream, std::string& cmd)
  {
    if (!(stream >> cmd))
    {
      return false;
    }
    return true;
  }

  void dispatchCommand(
    const std::string& cmdLine,
    const std::vector< ahrameev::Polygon >& polygons,
    const ahrameev::BoundingBox& globalBox)
  {
    if (cmdLine.empty())
    {
      std::cout << "<INVALID COMMAND>\n";
      return;
    }
    std::istringstream cmdStream(cmdLine);
    std::string cmd;
    if (!readCommandName(cmdStream, cmd))
    {
      std::cout << "<INVALID COMMAND>\n";
      return;
    }
    if (cmd == "PERMS")
    {
      ahrameev::handlePermsCommand(polygons, cmdStream);
    }
    else if (cmd == "INFRAME")
    {
      ahrameev::handleInFrameCommand(globalBox, cmdStream);
    }
    else
    {
      std::cout << "<INVALID COMMAND>\n";
    }
  }

  void processCommandLoop(
    const std::vector< ahrameev::Polygon >& polygons,
    const ahrameev::BoundingBox& globalBox)
  {
    std::string cmdLine;
    while (std::getline(std::cin, cmdLine))
    {
      dispatchCommand(cmdLine, polygons, globalBox);
    }
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
  processCommandLoop(polygons, globalBox);
  return 0;
}