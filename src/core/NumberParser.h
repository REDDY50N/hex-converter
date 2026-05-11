//
// Created by polar on 11.05.26.
//

#pragma once

#include "NumberBase.h"

#include <optional>
#include <QString>

class NumberParser
{
public:
  /// Parse text input depending on the users given bqase format
  static std::optional<std::uint64_t> parseUnsigned(const QString& text, NumberBase base);
};