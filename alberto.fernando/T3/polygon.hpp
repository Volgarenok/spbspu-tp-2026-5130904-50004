#ifndef POLYGON_HPP
#define POLYGON_HPP

#include <istream>
#include <ostream>
#include <string>
#include <vector>

namespace alberto {

struct Point
{
  int x = 0;
  int y = 0;
};

struct Polygon
{
  std::vector< Point > points;
};

std::istream& operator>>(std::istream& in, Point& p);
std::istream& operator>>(std::istream& in, Polygon& poly);
std::ostream& operator<<(std::ostream& out, const Point& p);
std::ostream& operator<<(std::ostream& out, const Polygon& poly);
bool operator==(const Point& a, const Point& b);
bool operator==(const Polygon& a, const Polygon& b);

double polygonArea(const Polygon& poly);

void cmdArea   (std::ostream& out, const std::vector< Polygon >& polys,
                const std::string& arg);
void cmdMax    (std::ostream& out, const std::vector< Polygon >& polys,
                const std::string& arg);
void cmdMin    (std::ostream& out, const std::vector< Polygon >& polys,
                const std::string& arg);
void cmdCount  (std::ostream& out, const std::vector< Polygon >& polys,
                const std::string& arg);
void cmdEcho   (std::ostream& out, std::vector< Polygon >& polys,
                std::istream& in);
void cmdRmecho (std::ostream& out, std::vector< Polygon >& polys,
                std::istream& in);

}

#endif
