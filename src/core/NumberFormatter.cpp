//
// Created by polar on 11.05.26.
//

#include "NumberFormatter.h"

// ----------------------------------------------
// CONVERT TO BINARY
// ----------------------------------------------
QString NumberFormatter::toBinary(std::uint64_t value, int width)
{
  // -- Default return string is zero
  QString out{"0"};

  do {
    // -- Compare LSB with 1 and add 1 if yes, else add 0
    out.prepend((value & 1ULL) ? QLatin1Char('1') : QLatin1Char('0'));

    // -- Shift right to remove last processed bit
    value >>= 1ULL;
  } while (value != 0ULL);

  // -- Add leading zeros to fill empty spaces
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