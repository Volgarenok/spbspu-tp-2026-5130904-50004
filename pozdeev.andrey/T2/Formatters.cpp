#include "Formatters.hpp"
#include <iomanip>

namespace pozdeev
{
  IOGuard::IOGuard(std::basic_ios< char >& s):
    s_(s),
    flags_(s.flags()),
    precision_(s.precision()),
    fill_(s.fill())
  {
  }

  IOGuard::~IOGuard()
  {
    s_.flags(flags_);
    s_.precision(precision_);
    s_.fill(fill_);
  }

  std::istream& operator>>(std::istream& in, DelimiterIO&& dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    char c = '0';
    in >> c;
    if (in && (c != dest.exp))
    {
      in.setstate(std::ios::failbit);
    }
    return in;
  }

  std::istream& operator>>(std::istream& in, StringIO&& dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    return in >> std::quoted(dest.ref);
  }

  std::ostream& operator<<(std::ostream& out, const StringOut& dest)
  {
    std::ostream::sentry sentry(out);
    if (!sentry)
    {
      return out;
    }
    return out << std::quoted(dest.val);
  }
}
