//
// Created by polar on 11.05.26.
//

#include "NumberFormatter.h"

// ----------------------------------------------
// CONVERT TO BINARY
// ----------------------------------------------
QString NumberFormatter::toBinary(std::uint64_t value, int width)
{
  // -- Special case: Return 0 as "0"
  if (value == 0ULL) {
    QString out{"0"};

    if (width > 0 && out.size() < width) {
      out = QString(width - out.size(), QLatin1Char('0')) + out;
    }

    return out;
  }

  // -- Start with empty string (do not initialize with 0)
  QString out{};

  while (value != 0ULL) {

    // -- Take least significant bit and prepend it to the output string
    out.prepend((value & 1ULL) ? QLatin1Char('1') : QLatin1Char('0'));

    // -- Remove this bit by right shift to process the next bit in the next iteration
    value >>= 1ULL;
  }

  // -- Fill with leading 0
  if (width > 0 && out.size() < width) {
    out = QString(width - out.size(), QLatin1Char('0')) + out;
  }

  return out;
}

// ----------------------------------------------
// CONVERT TO HEX
// ----------------------------------------------
QString NumberFormatter::toHex(std::uint64_t value, int width)
{
  // -- Format QString::number to base 16 (hex)
  QString out = QString::number(value, 16).toUpper();

  // -- Add leading zeros to fill empty spaces
  if (width > 0 && out.size() < width) {
    out = QString(width - out.size(), QLatin1Char('0')) + out;
  }

  return out;
}

// ----------------------------------------------
// STRING BUILDER
// ----------------------------------------------
QString NumberFormatter::describeValue(std::uint64_t value)
{
  // -- Concatinate all format strings together
  return QString("dec: %1\nhex: 0x%2\nbin: 0b%3")
      .arg(value)
      .arg(toHex(value))
      .arg(toBinary(value));
}