#include "io_formats.hpp"

namespace chadin {
  FormatGuard::FormatGuard(std::basic_ios<char>& stream):
    stream_(stream),
    fill_(stream.fill()),
    precision_(stream.precision()),
    flags_(stream.flags())
  {
  }

  FormatGuard::~FormatGuard()
  {
    stream_.fill(fill_);
    stream_.precision(precision_);
    stream_.flags(flags_);
  }
