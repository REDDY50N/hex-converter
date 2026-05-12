#include <catch2/catch_test_macros.hpp>
#include "NumberFormatter.h"
#include <QDebug>

// ----------------------------------------------
// TO BINARY
// ----------------------------------------------
TEST_CASE("We can create formatted binary value from input", "[NumberFormatter]")
{
  REQUIRE(NumberFormatter::toBinary(0) == "0");
  REQUIRE(NumberFormatter::toBinary(1) == "1");
  REQUIRE(NumberFormatter::toBinary(2) == "10");
  REQUIRE(NumberFormatter::toBinary(10) == "1010");
  REQUIRE(NumberFormatter::toBinary(1, 8) == "00000001");
}

// ----------------------------------------------
// TO HEX
// ----------------------------------------------
TEST_CASE("We can create formatted hex value from input", "[NumberFormatter]")
{
  REQUIRE(NumberFormatter::toHex(1) == "1");
  REQUIRE(NumberFormatter::toHex(1000) == "3E8");
  REQUIRE(NumberFormatter::toHex(255) == "FF");
  REQUIRE(NumberFormatter::toHex(1, 2) == "01");
}