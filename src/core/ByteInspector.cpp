#include "ByteInspector.h"
#include "NumberFormatter.h"

static QString byteToHex(std::uint64_t byteValue)
{
  return NumberFormatter::toHex(byteValue & 0xFFULL, 2);
}

ByteInspectorResult ByteInspector::inspect(std::uint64_t value, int byteCount)
{
  ByteInspectorResult result;
  result.value = value;
  result.byteCount = byteCount;

  for (int i = byteCount - 1; i >= 0; --i) {
    const std::uint64_t byteValue = (value >> (i * 8)) & 0xFFULL;
    result.bytesBigEndian.push_back(QStringLiteral("0x") + byteToHex(byteValue));
  }

  for (int i = 0; i < byteCount; ++i) {
    const std::uint64_t byteValue = (value >> (i * 8)) & 0xFFULL;
    result.bytesLittleEndian.push_back(QStringLiteral("0x") + byteToHex(byteValue));
  }

  result.lowByte = QStringLiteral("0x") + byteToHex(value & 0xFFULL);
  result.highByte = QStringLiteral("0x") + byteToHex((value >> 8ULL) & 0xFFULL);

  QString bits;
  for (int i = byteCount - 1; i >= 0; --i) {
    const std::uint64_t byteValue = (value >> (i * 8)) & 0xFFULL;
    bits += NumberFormatter::toBinary(byteValue, 8);
    if (i != 0) {
      bits += QLatin1Char(' ');
    }
  }
  result.bitGroups = bits;

  return result;
}