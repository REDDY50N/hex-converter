#include "ConversionResult.h"
#include "NumberFormatter.h"

QString ConversionResult::decimalText() const
{
  return QString::number(value);
}

QString ConversionResult::hexText() const
{
  return QStringLiteral("0x") + NumberFormatter::toHex(value);
}

QString ConversionResult::binaryText() const
{
  return QStringLiteral("0b") + NumberFormatter::toBinary(value);
}