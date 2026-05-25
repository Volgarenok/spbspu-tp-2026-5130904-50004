#define BOOST_TEST_MODULE T3Tests
#include <boost/test/included/unit_test.hpp>

#include "commands.hpp"
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

BOOST_AUTO_TEST_CASE(vertex_count_helpers_test)
{
  std::istringstream input("4 (0;0) (2;0) (2;2) (0;2)");

  aydogan::Polygon polygon;

  input >> polygon;

  BOOST_REQUIRE(input);
  BOOST_CHECK(aydogan::hasEvenVertexCount(polygon));
  BOOST_CHECK(!aydogan::hasOddVertexCount(polygon));
  BOOST_CHECK(aydogan::hasVertexCount(polygon, 4));
  BOOST_CHECK_EQUAL(aydogan::getVertexCount(polygon), 4);
}

BOOST_AUTO_TEST_CASE(permutation_test)
{
  std::istringstream firstInput("4 (0;0) (2;0) (2;2) (0;2)");
  std::istringstream secondInput("4 (2;2) (0;2) (0;0) (2;0)");

  aydogan::Polygon first;
  aydogan::Polygon second;

  firstInput >> first;
  secondInput >> second;

  BOOST_REQUIRE(firstInput);
  BOOST_REQUIRE(secondInput);
  BOOST_CHECK(aydogan::isPermutationOf(first, second));
}

BOOST_AUTO_TEST_CASE(right_angle_test)
{
  std::istringstream input("3 (0;0) (4;0) (0;3)");

  aydogan::Polygon polygon;

  input >> polygon;

  BOOST_REQUIRE(input);
  BOOST_CHECK(aydogan::hasRightAngle(polygon));
}

BOOST_AUTO_TEST_CASE(area_commands_test)
{
  aydogan::PolygonList polygons;

  std::istringstream triangleInput("3 (0;0) (4;0) (0;3)");
  std::istringstream squareInput("4 (0;0) (2;0) (2;2) (0;2)");

  aydogan::Polygon triangle;
  aydogan::Polygon square;

  triangleInput >> triangle;
  squareInput >> square;

  polygons.push_back(triangle);
  polygons.push_back(square);

  std::ostringstream output;

  aydogan::printAreaOdd(polygons, output);
  aydogan::printAreaEven(polygons, output);
  aydogan::printAreaMean(polygons, output);

  BOOST_CHECK_EQUAL(output.str(), "6.0\n4.0\n5.0\n");
}

BOOST_AUTO_TEST_CASE(count_and_extreme_commands_test)
{
  aydogan::PolygonList polygons;

  std::istringstream triangleInput("3 (0;0) (4;0) (0;3)");
  std::istringstream squareInput("4 (0;0) (2;0) (2;2) (0;2)");

  aydogan::Polygon triangle;
  aydogan::Polygon square;

  triangleInput >> triangle;
  squareInput >> square;

  polygons.push_back(triangle);
  polygons.push_back(square);

  std::ostringstream output;

  aydogan::printCountOdd(polygons, output);
  aydogan::printCountEven(polygons, output);
  aydogan::printMaxArea(polygons, output);
  aydogan::printMinVertexes(polygons, output);

  BOOST_CHECK_EQUAL(output.str(), "1\n1\n6.0\n3\n");
}

BOOST_AUTO_TEST_CASE(variant_commands_test)
{
  aydogan::PolygonList polygons;

  std::istringstream firstInput("4 (0;0) (2;0) (2;2) (0;2)");
  std::istringstream secondInput("4 (2;2) (0;2) (0;0) (2;0)");
  std::istringstream thirdInput("3 (0;0) (4;0) (0;3)");

  aydogan::Polygon first;
  aydogan::Polygon second;
  aydogan::Polygon third;

  firstInput >> first;
  secondInput >> second;
  thirdInput >> third;

  polygons.push_back(first);
  polygons.push_back(second);
  polygons.push_back(third);

  std::ostringstream output;

  aydogan::printPerms(polygons, first, output);
  aydogan::printRightShapes(polygons, output);

  BOOST_CHECK_EQUAL(output.str(), "2\n3\n");
}

BOOST_AUTO_TEST_CASE(run_commands_test)
{
  aydogan::PolygonList polygons;

  std::istringstream triangleInput("3 (0;0) (4;0) (0;3)");
  std::istringstream squareInput("4 (0;0) (2;0) (2;2) (0;2)");

  aydogan::Polygon triangle;
  aydogan::Polygon square;

  triangleInput >> triangle;
  squareInput >> square;

  polygons.push_back(triangle);
  polygons.push_back(square);

  std::istringstream commands(
    "AREA ODD\n"
    "COUNT EVEN\n"
    "RIGHTSHAPES\n"
    "BAD COMMAND\n"
  );

  std::ostringstream output;

  aydogan::runCommands(polygons, commands, output);

  BOOST_CHECK_EQUAL(output.str(), "6.0\n1\n2\n<INVALID COMMAND>\n");
}
