//
// Created by polar on 11.05.26.
//

#pragma once

class QString;

// Number base format (choosen by user input from cli arg)
enum class NumberBase
{
  Decimal = 10,   // Dezimal: 0-9
  Hexadecimal = 16, // Hexadezimal: 0-9, A-F
  Binary = 2      // Binär: 0-1
};

/// Helper function to convert a text string to a number base format
NumberBase numberBaseFromString(const QString& text);