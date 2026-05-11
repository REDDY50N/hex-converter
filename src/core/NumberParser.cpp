//
// Created by polar on 11.05.26.
//

#include "NumberParser.h"

#include <charconv>     // std::from_chars
#include <system_error> // std::errc

// ----------------------------------------------
// PARSE NUM STRING FROM CLI (UNSIGNED ONLY)
// ----------------------------------------------
std::optional<std::uint64_t> NumberParser::parseUnsigned(const QString& text, NumberBase base)
{
  // Parsed String to Unicode Byte Array
  // QString ist intern kein nullterminierter char-string, sondern sondern nrutzt Referenzzählung und Länge
  // daher Wandlung in UTF-8; alternativ: QString::toUtf8().constData()/ QString::toLocal8Bit().constData()
  const QByteArray utf8 = text.toUtf8();

  // -- Pointer to first address of raw bytes from user input text
  const char* first = utf8.constData();

  // -- Pointer on last valid char
  const char* last = first + utf8.size();

  // -- Var to save value using from_chars (if no error code / on success)
  std::uint64_t value = 0;

  // -- Parse address values from char into number
  // std::from_chars parses from [first, last] into number
  // Returns:
  // - ptr: Points to positon of last successful parsed char
  // - ec: Error-Code ... invalid_argument / result_out_of_range
  auto result = std::from_chars(first, last, value, static_cast<int>(base));

  // -- Error Check:
  // 1) result.ec contains no error
  // 2) result.ptr has to be exactly last (to parse everything, let nothing unparsed)
  if (result.ec != std::errc{} || result.ptr != last) {
    return std::nullopt;
  }

  return value;
}