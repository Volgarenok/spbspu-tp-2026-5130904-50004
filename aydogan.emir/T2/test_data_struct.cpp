#define BOOST_TEST_MODULE T2Tests
#include <boost/test/included/unit_test.hpp>

#include "data_struct.hpp"

#include <sstream>
#include <string>

BOOST_AUTO_TEST_CASE(read_key_order_123_test)
{
  std::istringstream input("(:key1 89ull:key2 0b100101:key3 \"Data\":)");

  aydogan::DataStruct data{};

  input >> data;

  BOOST_REQUIRE(input);
  BOOST_CHECK_EQUAL(data.key1, 89ull);
  BOOST_CHECK_EQUAL(data.key2, 37ull);
  BOOST_CHECK_EQUAL(data.key3, "Data");
}

BOOST_AUTO_TEST_CASE(read_key_order_231_test)
{
  std::istringstream input("(:key2 0B100101:key3 \"Data\":key1 89ULL:)");

  aydogan::DataStruct data{};

  input >> data;

  BOOST_REQUIRE(input);
  BOOST_CHECK_EQUAL(data.key1, 89ull);
  BOOST_CHECK_EQUAL(data.key2, 37ull);
  BOOST_CHECK_EQUAL(data.key3, "Data");
}

BOOST_AUTO_TEST_CASE(output_format_test)
{
  aydogan::DataStruct data{89ull, 37ull, "Data"};

  std::ostringstream output;

  output << data;

  BOOST_CHECK_EQUAL(output.str(), "(:key1 89ull:key2 0b100101:key3 \"Data\":)");
}

BOOST_AUTO_TEST_CASE(output_zero_binary_test)
{
  aydogan::DataStruct data{1ull, 0ull, "Zero"};

  std::ostringstream output;

  output << data;

  BOOST_CHECK_EQUAL(output.str(), "(:key1 1ull:key2 0b0:key3 \"Zero\":)");
}
