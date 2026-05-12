#include <catch2/catch_test_macros.hpp>
#include <QString>
#include "NumberBase.h"


TEST_CASE("We can convert QString values from Qt's CLI parser arg into an Enum for the base", "[NumberBase]")
{
  SECTION("Decimal")
  {
    NumberBase nb = numberBaseFromString(QString("dec"));
    REQUIRE( nb == NumberBase::Decimal);
  }

  SECTION("Hexadecimal")
  {
    NumberBase nb = numberBaseFromString(QString("hex"));
    REQUIRE( nb == NumberBase::Hexadecimal);
  }

  SECTION("Binary")
  {
    NumberBase nb = numberBaseFromString(QString("bin"));
    REQUIRE( nb == NumberBase::Binary);
  }

  SECTION("Empty is defaulted to decimal")
  {
    NumberBase nb = numberBaseFromString(QString(""));
    REQUIRE( nb == NumberBase::Decimal);
  }
}
