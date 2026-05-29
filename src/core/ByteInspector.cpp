#include "ByteInspector.h"
#include "NumberFormatter.h"

/**
 * @file ByteInspector.cpp
 * @brief Implementierung der Byte-Inspektion für den Hex-Analyser.
 *
 * Diese Datei enthält die Implementierung der ByteInspector-Klasse, die
 * einen numerischen Wert in seine einzelnen Bytes zerlegt und in
 * verschiedenen Darstellungsformen (Big-Endian, Little-Endian, Binär)
 * zurückgibt.
 *
 * @see ByteInspector.h
 */

// ----------------------------------------------
// -- CONVERT BYTE TO HEX
// ----------------------------------------------
/**
 * @brief Konvertiert ein einzelnes Byte in eine zweistellige Hexadezimal-Zeichenkette.
 *
 * Diese Hilfsfunktion maskiert den übergebenen Wert auf das niederwertigste Byte
 * (8 Bit) und formatiert ihn als zweistellige Hexadezimalzahl.
 *
 * @param[in] byteValue Der zu konvertierende Wert. Es werden nur die unteren 8 Bit verwendet.
 * @return QString Die hexadezimale Darstellung im Format "XX" (z.B. "0A", "FF").
 *
 * @note Der Parameter wird mit @c 0xFFULL maskiert, sodass nur das niederwertigste
 *       Byte berücksichtigt wird, unabhängig von höherwertigen Bits.
 *
 * @see NumberFormatter::toHex()
 */
static QString byteToHex(std::uint64_t byteValue)
{
  return NumberFormatter::toHex(byteValue & 0xFFULL, 2);
}

// ----------------------------------------------
// -- INSPECT BYTE
// ----------------------------------------------
/**
 * @brief Zerlegt einen numerischen Wert in seine Byte-Komponenten.
 *
 * Diese Methode analysiert einen vorzeichenlosen 64-Bit-Wert und zerlegt ihn
 * in die angegebene Anzahl von Bytes. Die Ergebnisse werden in verschiedenen
 * Formaten zurückgegeben: Big-Endian, Little-Endian, Low-/High-Byte sowie
 * als gruppierte Binärdarstellung.
 *
 * @param[in] value Der zu analysierende numerische Wert (max. 64 Bit).
 * @param[in] byteCount Die Anzahl der Bytes, die aus @p value extrahiert werden sollen.
 *                    Typischerweise 1, 2, 4 oder 8.
 *
 * @return ByteInspectorResult Ein Struktur mit allen Zerlegungsergebnissen.
 *
 * @par Beispiel:
 * @code
 * ByteInspector inspector;
 * auto result = inspector.inspect(0x1234ABCD, 4);
 * // result.bytesBigEndian:    ["0x12", "0x34", "0xAB", "0xCD"]
 * // result.bytesLittleEndian: ["0xCD", "0xAB", "0x34", "0x12"]
 * // result.lowByte:           "0xCD"
 * // result.highByte:          "0xAB"
 * // result.bitGroups:         "00010010 00110100 10101011 11001101"
 * @endcode
 *
 * @warning Wenn @p byteCount größer als 8 ist, können unerwartete Ergebnisse
 *          auftreten, da @p value nur 64 Bit umfasst.
 *
 * @see ByteInspectorResult
 * @see NumberFormatter::toBinary()
 */
ByteInspectorResult ByteInspector::inspect(std::uint64_t value, int byteCount)
{

  // -- Vars
  ByteInspectorResult result;
  result.value = value;
  result.byteCount = byteCount;

  for (int i = byteCount - 1; i >= 0; --i) {
    const std::uint64_t byteValue = (value >> (i * 8)) & 0xFFULL;
    result.bytesBigEndian.push_back(QStringLiteral("0x") + byteToHex(byteValue));
  }

  for (int i = 0; i < byteCount; ++i) {
    const std::uint64_t byteValue = (value >> (i * 8)) & 0xFFULL;
    result.bytesLittleEndian.push_back(QStringLiteral("0x") + byteToHex(byteValue));
  }

  result.lowByte = QStringLiteral("0x") + byteToHex(value & 0xFFULL);
  result.highByte = QStringLiteral("0x") + byteToHex((value >> 8ULL) & 0xFFULL);

  QString bits;
  for (int i = byteCount - 1; i >= 0; --i) {
    const std::uint64_t byteValue = (value >> (i * 8)) & 0xFFULL;
    bits += NumberFormatter::toBinary(byteValue, 8);
    if (i != 0) {
      bits += QLatin1Char(' ');
    }
  }
  result.bitGroups = bits;

  return result;
}