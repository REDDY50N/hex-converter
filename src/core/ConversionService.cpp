#include "ConversionService.h"
#include "NumberParser.h"
#include "NumberBase.h"
#include "ByteInspector.h"

ConversionResult ConversionService::convert(const QString& inputText, const QString& inputBase)
{
  ConversionResult result;
  result.inputText = inputText;
  result.inputBase = inputBase;

  const NumberBase base = numberBaseFromString(inputBase);
  const auto parsed = NumberParser::parseUnsigned(inputText, base);

  if (!parsed.has_value()) {
    result.ok = false;
    result.errorMessage = QStringLiteral("Could not parse input.");
    return result;
  }

  result.ok = true;
  result.value = *parsed;
  return result;
}