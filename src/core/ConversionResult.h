#pragma once

#include <QString>
#include <cstdint>

struct ConversionResult
{
  bool ok = false;
  std::uint64_t value = 0;
  QString inputText;
  QString inputBase;
  QString errorMessage;

  QString decimalText() const;
  QString hexText() const;
  QString binaryText() const;
};