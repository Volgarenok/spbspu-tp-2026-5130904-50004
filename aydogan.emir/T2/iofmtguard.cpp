#include "iofmtguard.hpp"

aydogan::IOFmtGuard::IOFmtGuard(std::basic_ios< char >& stream):
  stream_(stream),
  width_(stream.width()),
  precision_(stream.precision()),
  flags_(stream.flags()),
  fill_(stream.fill())
{}

aydogan::IOFmtGuard::~IOFmtGuard()
{
  stream_.width(width_);
  stream_.precision(precision_);
  stream_.flags(flags_);
  stream_.fill(fill_);
}
