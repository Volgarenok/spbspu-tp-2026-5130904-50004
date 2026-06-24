#include "polygon.hpp"

namespace ahrameev
{

  namespace
  {

    bool expectChar(std::istream& is, char expected)
    {
      char c = 0;
      if (!(is >> c))
      {
        return false;
      }
      if (c != expected)
      {
        return false;
      }
      return true;
    }

    bool readInt(std::istream& is, int& value)
    {
      if (!(is >> value))
      {
        return false;
      }
      return true;
    }

    bool readCoordinate(std::istream& is, Point& p)
    {
      if (!expectChar(is, '('))
      {
        return false;
      }
      if (!readInt(is, p.x))
      {
        return false;
      }
      if (!expectChar(is, ';'))
      {
        return false;
      }
      if (!readInt(is, p.y))
      {
        return false;
      }
      if (!expectChar(is, ')'))
      {
        return false;
      }
      return true;
    }

    bool readVertexCount(std::istream& is, std::size_t& count)
    {
      if (!(is >> count))
      {
        return false;
      }
      if (count == 0)
      {
        return false;
      }
      return true;
    }

    bool readAllVertices(std::istream& is, std::vector< Point >& points, std::size_t count)
    {
      points.clear();
      points.reserve(count);
      for (std::size_t i = 0; i < count; ++i)
      {
        Point p{};
        if (!readCoordinate(is, p))
        {
          return false;
        }
        points.push_back(p);
      }
      return true;
    }

  }

  std::istream& readPoint(std::istream& is, Point& p)
  {
    if (!readCoordinate(is, p))
    {
      is.setstate(std::ios::failbit);
    }
    return is;
  }

  std::istream& readPolygon(std::istream& is, Polygon& poly)
  {
    std::size_t count = 0;
    if (!readVertexCount(is, count))
    {
      is.setstate(std::ios::failbit);
      return is;
    }
    if (!readAllVertices(is, poly.points, count))
    {
      is.setstate(std::ios::failbit);
      return is;
    }
    return is;
  }

}