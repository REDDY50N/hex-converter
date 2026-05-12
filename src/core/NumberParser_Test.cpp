#include <catch2/catch_test_macros.hpp>
#include "NumberParser.h"

// ----------------------------------------------
// DECIMAL STRING TO DEC
// ----------------------------------------------
TEST_CASE("We can parse decimal value strings and convert them to decimal", "[NumberParser]")
{
  SECTION("Decimal 0")
  {
    auto result = NumberParser::parseUnsigned("0", NumberBase::Decimal);
    CHECK(result == 0);
  }

  SECTION("Decimal 16")
  {
    auto result = NumberParser::parseUnsigned("16", NumberBase::Decimal);
    CHECK(result == 16);
  }

  // -- Negative is not allowed in unsigend parser, so it should return nullopt
  SECTION("Decimal -1")
  {
    auto result = NumberParser::parseUnsigned("-1", NumberBase::Decimal);
    CHECK(result == std::nullopt);
  }
}

// ----------------------------------------------
// HEX STRING TO DEC
// ----------------------------------------------
TEST_CASE("We can parse hex value strings and convert them to decimal", "[NumberParser]")
{

  SECTION("Hexadecimal 00")
  {
    auto result = NumberParser::parseUnsigned("00", NumberBase::Hexadecimal);
    CHECK(result == 0);
  }

  SECTION("Hexadecimal 1A")
  {
    auto result = NumberParser::parseUnsigned("1A", NumberBase::Hexadecimal);
    CHECK(result == 26);
  }
}

// ----------------------------------------------
// BINARY STRING TO DEC
// ----------------------------------------------
TEST_CASE("We can parse binary value strings and convert them to decimal", "[NumberParser]")
{

  SECTION("Binary 00")
  {
    auto result = NumberParser::parseUnsigned("00", NumberBase::Binary);
    CHECK(result == 0);
  }

  SECTION("Binary 00000000")
  {
    auto result = NumberParser::parseUnsigned("00000000", NumberBase::Binary);
    CHECK(result == 0);
  }

  SECTION("Binary 00001010")
  {
    auto result = NumberParser::parseUnsigned("00001010", NumberBase::Binary);
    CHECK(result == 10);
  }
}
