#ifndef DATA_STRUCT_HPP
#define DATA_STRUCT_HPP

#include <iosfwd>
#include <string>

namespace aydogan
{
  struct DataStruct
  {
    unsigned long long key1;
    unsigned long long key2;
    std::string key3;
  };

  struct DelimiterIO
  {
    char expected;
  };

  struct LabelIO
  {
    std::string expected;
  };

  struct StringIO
  {
    std::string& value;
  };

  struct UllLiteralIO
  {
    unsigned long long& value;
  };

  struct UllBinaryIO
  {
    unsigned long long& value;
  };

  std::istream& operator>>(std::istream& input, DelimiterIO&& data);
  std::istream& operator>>(std::istream& input, LabelIO&& data);
  std::istream& operator>>(std::istream& input, StringIO&& data);
  std::istream& operator>>(std::istream& input, UllLiteralIO&& data);
  std::istream& operator>>(std::istream& input, UllBinaryIO&& data);
  std::istream& operator>>(std::istream& input, DataStruct& data);

  std::ostream& operator<<(std::ostream& output, const DataStruct& data);

  bool compareData(const DataStruct& left, const DataStruct& right);
}

#endif
