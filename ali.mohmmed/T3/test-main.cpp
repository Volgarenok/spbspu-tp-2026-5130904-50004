#define BOOST_TEST_MODULE T3
#include <boost/test/included/unit_test.hpp>

#include <sstream>

#include "geometry.hpp"

BOOST_AUTO_TEST_CASE(point_input)
{
  std::stringstream input("(1;2)");

  ali::Point point{};

  input >> point;

  BOOST_TEST(point.x == 1);
  BOOST_TEST(point.y == 2);
}

BOOST_AUTO_TEST_CASE(polygon_area)
{
  ali::Polygon polygon;

  polygon.points.push_back({0, 0});
  polygon.points.push_back({4, 0});
  polygon.points.push_back({4, 4});
  polygon.points.push_back({0, 4});

  BOOST_TEST(ali::getArea(polygon) == 16.0);
}

BOOST_AUTO_TEST_CASE(rectangle_check)
{
  ali::Polygon polygon;

  polygon.points.push_back({0, 0});
  polygon.points.push_back({1, 0});
  polygon.points.push_back({1, 1});
  polygon.points.push_back({0, 1});

  BOOST_TEST(ali::isRectangle(polygon));
}
