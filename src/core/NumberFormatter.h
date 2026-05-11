//
// Created by polar on 11.05.26.
//

#pragma once

#include <QString>
#include <cstdint>

// Helper class to format numbers in different bases and create a string for cli output
class NumberFormatter
{
public:
  static QString toBinary(std::uint64_t value, int width = 0);
  static QString toHex(std::uint64_t value, int width = 0);
  static QString describeValue(std::uint64_t value);
};