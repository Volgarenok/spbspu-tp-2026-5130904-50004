#define BOOST_TEST_MODULE T3Tests
#include <boost/test/included/unit_test.hpp>

#include "geometry.hpp"

#include <sstream>
#include <string>

BOOST_AUTO_TEST_CASE(read_point_test)
{
  std::istringstream input("(10;-5)");

  aydogan::Point point{0, 0};

  input >> point;

  BOOST_REQUIRE(input);
  BOOST_CHECK_EQUAL(point.x, 10);
  BOOST_CHECK_EQUAL(point.y, -5);
}

BOOST_AUTO_TEST_CASE(read_polygon_test)
{
  std::istringstream input("3 (0;0) (4;0) (0;3)");

  aydogan::Polygon polygon;

  input >> polygon;

  BOOST_REQUIRE(input);
  BOOST_CHECK_EQUAL(polygon.points.size(), 3);
  BOOST_CHECK_EQUAL(polygon.points[0].x, 0);
  BOOST_CHECK_EQUAL(polygon.points[1].x, 4);
  BOOST_CHECK_EQUAL(polygon.points[2].y, 3);
}

BOOST_AUTO_TEST_CASE(output_polygon_test)
{
  aydogan::Polygon polygon;
  polygon.points.push_back(aydogan::Point{0, 0});
  polygon.points.push_back(aydogan::Point{1, 0});
  polygon.points.push_back(aydogan::Point{0, 1});

  std::ostringstream output;

  output << polygon;

  BOOST_CHECK_EQUAL(output.str(), "3 (0;0) (1;0) (0;1) ");
}

BOOST_AUTO_TEST_CASE(area_triangle_test)
{
  std::istringstream input("3 (0;0) (4;0) (0;3)");

  aydogan::Polygon polygon;

  input >> polygon;

  BOOST_REQUIRE(input);
  BOOST_CHECK_CLOSE(aydogan::getArea(polygon), 6.0, 0.001);
}

BOOST_AUTO_TEST_CASE(area_square_test)
{
  std::istringstream input("4 (0;0) (2;0) (2;2) (0;2)");

  aydogan::Polygon polygon;

  input >> polygon;

  BOOST_REQUIRE(input);
  BOOST_CHECK_CLOSE(aydogan::getArea(polygon), 4.0, 0.001);
}
