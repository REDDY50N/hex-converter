//
// Created by polar on 11.05.26.
//

#include "NumberBase.h"

#include <QString>

// Convert text from cli arg to enum-value (from users cli input)
NumberBase numberBaseFromString(const QString& text)
{
  const auto lower = text.toLower();

  if (lower == "dec") {
    return NumberBase::Decimal;
  }

  if (lower == "hex") {
    return NumberBase::Hexadecimal;
  }

  if (lower == "bin") {
    return NumberBase::Binary;
  }

  // Fallback: Just use decimal if something went wrong
  return NumberBase::Decimal;
}