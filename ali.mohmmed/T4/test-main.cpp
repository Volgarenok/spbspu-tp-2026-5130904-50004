#define BOOST_TEST_MODULE T4
#include <boost/test/included/unit_test.hpp>

#include "rectangle.hpp"

BOOST_AUTO_TEST_CASE(rectangle_area)
{
  ali::Rectangle rect(
    10.0,
    5.0,
    {0.0, 0.0});

  BOOST_TEST(rect.getArea() == 50.0);
}
