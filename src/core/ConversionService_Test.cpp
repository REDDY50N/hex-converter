#include <catch2/catch_test_macros.hpp>
#include "ConversionService.h"

TEST_CASE("ConversionService converts decimal input correctly", "[ConversionService]")
{
  const ConversionResult result = ConversionService::convert("1", "dec");

  REQUIRE(result.ok);
  REQUIRE(result.value == 1ULL);
  REQUIRE(result.decimalText() == "1");
  REQUIRE(result.hexText() == "0x1");
  REQUIRE(result.binaryText() == "0b1");
}

TEST_CASE("ConversionService converts hex input correctly", "[ConversionService]")
{
  const ConversionResult result = ConversionService::convert("FF", "hex");

  REQUIRE(result.ok);
  REQUIRE(result.value == 255ULL);
  REQUIRE(result.decimalText() == "255");
  REQUIRE(result.hexText() == "0xFF");
  REQUIRE(result.binaryText() == "0b11111111");
}

TEST_CASE("ConversionService converts binary input correctly", "[ConversionService]")
{
  const ConversionResult result = ConversionService::convert("1010", "bin");

  REQUIRE(result.ok);
  REQUIRE(result.value == 10ULL);
  REQUIRE(result.decimalText() == "10");
  REQUIRE(result.hexText() == "0xA");
  REQUIRE(result.binaryText() == "0b1010");
}

TEST_CASE("ConversionService rejects invalid input", "[ConversionService]")
{
  const ConversionResult result = ConversionService::convert("12AB", "dec");

  REQUIRE_FALSE(result.ok);
  REQUIRE_FALSE(result.errorMessage.isEmpty());
}