#define BOOST_TEST_MODULE T2
#include <boost/test/included/unit_test.hpp>

#include <sstream>

#include "data-struct.hpp"

BOOST_AUTO_TEST_CASE(read_test)
{
  std::stringstream input(
    "(:key1 'a':key2 5.0e+2:key3 \"hello\":)");

  ali::DataStruct data{};

  input >> data;

  BOOST_TEST(data.key1 == 'a');
  BOOST_TEST(data.key3 == "hello");
}

BOOST_AUTO_TEST_CASE(sort_test)
{
  ali::DataStruct a{ 'a', 1.0, "x" };
  ali::DataStruct b{ 'b', 1.0, "x" };

  BOOST_TEST(a < b);
}
