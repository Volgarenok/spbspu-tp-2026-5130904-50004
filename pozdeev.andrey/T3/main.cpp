#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>
#include <string>
#include <limits>
#include "Geometry.hpp"
#include "Commands.hpp"

int main(int argc, char* argv[])
{
  if (argc != 2)
  {
    std::cerr << "File name is required" << '\n';
    return 1;
  }

  std::ifstream file(argv[1]);
  if (!file)
  {
    std::cerr << "Cannot open file" << '\n';
    return 1;
  }

  std::vector< pozdeev::Polygon > polygons;
  while (!file.eof())
  {
    std::copy(
      std::istream_iterator< pozdeev::Polygon >(file),
      std::istream_iterator< pozdeev::Polygon >(),
      std::back_inserter(polygons)
    );
    if (file.fail() && !file.eof())
    {
      file.clear();
      file.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }

  std::string cmd;
  while (std::cin >> cmd)
  {
    try
    {
      if (cmd == "AREA")
      {
        pozdeev::executeArea(polygons, std::cin, std::cout);
      }
      else if (cmd == "MAX")
      {
        pozdeev::executeMax(polygons, std::cin, std::cout);
      }
      else if (cmd == "MIN")
      {
        pozdeev::executeMin(polygons, std::cin, std::cout);
      }
      else if (cmd == "COUNT")
      {
        pozdeev::executeCount(polygons, std::cin, std::cout);
      }
      else if (cmd == "INFRAME")
      {
        pozdeev::executeInframe(polygons, std::cin, std::cout);
      }
      else if (cmd == "SAME")
      {
        pozdeev::executeSame(polygons, std::cin, std::cout);
      }
      else
      {
        throw std::invalid_argument("Invalid command");
      }
    }
    catch (const std::exception&)
    {
      std::cout << "<INVALID COMMAND>\n";
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }

  return 0;
}
