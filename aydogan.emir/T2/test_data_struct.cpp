#define BOOST_TEST_MODULE T2Tests
#include <boost/test/included/unit_test.hpp>

#include "data_struct.hpp"

#include <algorithm>
#include <sstream>
#include <string>
#include <vector>

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

BOOST_AUTO_TEST_CASE(compare_by_key1_test)
{
  aydogan::DataStruct first{1ull, 10ull, "bbb"};
  aydogan::DataStruct second{2ull, 1ull, "a"};

  BOOST_CHECK(aydogan::compareData(first, second));
  BOOST_CHECK(!aydogan::compareData(second, first));
}

BOOST_AUTO_TEST_CASE(compare_by_key2_test)
{
  aydogan::DataStruct first{1ull, 5ull, "bbb"};
  aydogan::DataStruct second{1ull, 10ull, "a"};

  BOOST_CHECK(aydogan::compareData(first, second));
  BOOST_CHECK(!aydogan::compareData(second, first));
}

BOOST_AUTO_TEST_CASE(compare_by_key3_length_test)
{
  aydogan::DataStruct first{1ull, 1ull, "a"};
  aydogan::DataStruct second{1ull, 1ull, "bbbb"};

  BOOST_CHECK(aydogan::compareData(first, second));
  BOOST_CHECK(!aydogan::compareData(second, first));
}

BOOST_AUTO_TEST_CASE(sort_vector_test)
{
  std::vector< aydogan::DataStruct > data;
  data.push_back(aydogan::DataStruct{2ull, 1ull, "a"});
  data.push_back(aydogan::DataStruct{1ull, 4ull, "long"});
  data.push_back(aydogan::DataStruct{1ull, 3ull, "medium"});
  data.push_back(aydogan::DataStruct{1ull, 3ull, "a"});

  std::sort(data.begin(), data.end(), aydogan::compareData);

  BOOST_CHECK_EQUAL(data[0].key1, 1ull);
  BOOST_CHECK_EQUAL(data[0].key2, 3ull);
  BOOST_CHECK_EQUAL(data[0].key3, "a");

  BOOST_CHECK_EQUAL(data[1].key1, 1ull);
  BOOST_CHECK_EQUAL(data[1].key2, 3ull);
  BOOST_CHECK_EQUAL(data[1].key3, "medium");

  BOOST_CHECK_EQUAL(data[2].key1, 1ull);
  BOOST_CHECK_EQUAL(data[2].key2, 4ull);
  BOOST_CHECK_EQUAL(data[2].key3, "long");

  BOOST_CHECK_EQUAL(data[3].key1, 2ull);
}

BOOST_AUTO_TEST_CASE(skip_invalid_line_test)
{
  std::istringstream input(
    "(:key1 1ull:key1 2ull:key2 0b1:key3 \"bad\":)\n"
    "(:key2 0b101:key3 \"good\":key1 7ull:)"
  );

  aydogan::DataStruct data{};

  input >> data;

  BOOST_REQUIRE(input);
  BOOST_CHECK_EQUAL(data.key1, 7ull);
  BOOST_CHECK_EQUAL(data.key2, 5ull);
  BOOST_CHECK_EQUAL(data.key3, "good");
}

BOOST_AUTO_TEST_CASE(invalid_duplicate_key_test)
{
  std::istringstream input("(:key1 1ull:key1 2ull:key2 0b1:key3 \"x\":)");

  aydogan::DataStruct data{};

  input >> data;

  BOOST_CHECK(!input);
}

BOOST_AUTO_TEST_CASE(invalid_binary_test)
{
  std::istringstream input("(:key1 1ull:key2 0b:key3 \"x\":)");

  aydogan::DataStruct data{};

  input >> data;

  BOOST_CHECK(!input);
}
