#include <catch2/catch_test_macros.hpp>
#include "NumberFormatter.h"
#include <QDebug>

// ----------------------------------------------
// TO BINARY
// ----------------------------------------------
TEST_CASE("We can create formated binary value from input", "[NumberFormater]")
{
  QString formated_value{};

  SECTION("0 toBinary")
  {
    formated_value = NumberFormatter::toBinary(0000);
    REQUIRE(formated_value == "0");
  }

  SECTION("1 toBinary")
  {
    formated_value = NumberFormatter::toBinary(1);
    REQUIRE(formated_value == "1");
  }

  SECTION("ULL Literal toBinary")
  {
    formated_value = NumberFormatter::toBinary(2);
    REQUIRE(formated_value == "10");
  }

  SECTION("10 toBinary")
  {
    formated_value = NumberFormatter::toBinary(10);
    REQUIRE(formated_value == "1010");
  }

}



// ----------------------------------------------
// TO HEX
// ----------------------------------------------
TEST_CASE("We can create formated hex value from input", "[NumberFormater]")
{
  QString formated_value{};

  SECTION("0 toHex")
  {
    formated_value = NumberFormatter::toHex(0001ULL);
    REQUIRE(formated_value == "1");
  }

  SECTION("1A toHex")
  {
    formated_value = NumberFormatter::toHex(1000);
    REQUIRE(formated_value == "3E8");
  }

  SECTION("255 toHex")
  {
    formated_value = NumberFormatter::toHex(255);
    REQUIRE(formated_value == "FF");
  }

}