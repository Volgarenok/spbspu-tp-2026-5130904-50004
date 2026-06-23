#include "data_struct.h"

#include <iomanip>
#include <iostream>

namespace
{
  class IOguard
  {
  public:
    explicit IOguard(std::basic_ios< char >& stream):
      stream_(stream),
      width_(stream.width()),
      precision_(stream.precision()),
      fmt_(stream.flags()),
      fill_(stream.fill())
    {
    }

    ~IOguard()
    {
      stream_.width(width_);
      stream_.precision(precision_);
      stream_.flags(fmt_);
      stream_.fill(fill_);
    }

  private:
    std::basic_ios< char >& stream_;
    std::streamsize width_;
    std::streamsize precision_;
    std::basic_ios< char >::fmtflags fmt_;
    char fill_;
  };
}

bool ahrameev::operator<(const DataStruct& lhs, const DataStruct& rhs)
{
  if (lhs.key1 != rhs.key1)
  {
    return lhs.key1 < rhs.key1;
  }
  if (lhs.key2 != rhs.key2)
  {
    return lhs.key2 < rhs.key2;
  }
  return lhs.key3.length() < rhs.key3.length();
}

std::ostream& ahrameev::operator<<(std::ostream& out, const DataStruct& src)
{
  IOguard guard(out);
  out << "(:key1 "
      << std::fixed << std::setprecision(1) << src.key1 << "d"
      << ":key2 " << src.key2 << "ll"
      << ":key3 \"" << src.key3 << "\":)";
  return out;
}