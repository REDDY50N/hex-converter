#pragma once

#include "ConversionResult.h"
#include <QString>

class ConversionService
{
public:
  static ConversionResult convert(const QString& inputText, const QString& inputBase);
};