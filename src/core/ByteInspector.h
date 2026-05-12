#pragma once

#include <cstdint>
#include <QStringList>

struct ByteInspectorResult
{
  std::uint64_t value = 0;
  int byteCount = 0;
  QStringList bytesBigEndian;
  QStringList bytesLittleEndian;
  QString highByte;
  QString lowByte;
  QString bitGroups;
};

class ByteInspector
{
public:
  static ByteInspectorResult inspect(std::uint64_t value, int byteCount = 8);
};