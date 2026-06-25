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

  std::istream& operator>>(std::istream& in, DelimiterIO&& dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry) {
      return in;
    }
    char current = '0';
    in >> current;
    if (in && current != dest.expected) {
      in.setstate(std::ios::failbit);
    }
    return in;
  }
