#include <catch2/catch_test_macros.hpp>

#include "ByteInspector.h"

TEST_CASE("ByteInspector inspects one byte correctly", "[ByteInspector]")
{
  const ByteInspectorResult result = ByteInspector::inspect(0x1ULL, 1);

  REQUIRE(result.value == 1ULL);
  REQUIRE(result.byteCount == 1);
  REQUIRE(result.lowByte == "0x01");
  REQUIRE(result.highByte == "0x00");
  REQUIRE(result.bytesBigEndian.size() == 1);
  REQUIRE(result.bytesLittleEndian.size() == 1);
  REQUIRE(result.bytesBigEndian[0] == "0x01");
  REQUIRE(result.bytesLittleEndian[0] == "0x01");
  REQUIRE(result.bitGroups == "00000001");
}

TEST_CASE("ByteInspector inspects two bytes correctly", "[ByteInspector]")
{
  const ByteInspectorResult result = ByteInspector::inspect(0x1234ULL, 2);

  REQUIRE(result.value == 0x1234ULL);
  REQUIRE(result.byteCount == 2);
  REQUIRE(result.lowByte == "0x34");
  REQUIRE(result.highByte == "0x12");
  REQUIRE(result.bytesBigEndian.size() == 2);
  REQUIRE(result.bytesLittleEndian.size() == 2);
  REQUIRE(result.bytesBigEndian[0] == "0x12");
  REQUIRE(result.bytesBigEndian[1] == "0x34");
  REQUIRE(result.bytesLittleEndian[0] == "0x34");
  REQUIRE(result.bytesLittleEndian[1] == "0x12");
  REQUIRE(result.bitGroups == "00010010 00110100");
}

TEST_CASE("ByteInspector inspects four bytes correctly", "[ByteInspector]")
{
  const ByteInspectorResult result = ByteInspector::inspect(0x12345678ULL, 4);

  REQUIRE(result.lowByte == "0x78");
  REQUIRE(result.highByte == "0x56");
  REQUIRE(result.bytesBigEndian[0] == "0x12");
  REQUIRE(result.bytesBigEndian[1] == "0x34");
  REQUIRE(result.bytesBigEndian[2] == "0x56");
  REQUIRE(result.bytesBigEndian[3] == "0x78");
  REQUIRE(result.bitGroups == "00010010 00110100 01010110 01111000");
}