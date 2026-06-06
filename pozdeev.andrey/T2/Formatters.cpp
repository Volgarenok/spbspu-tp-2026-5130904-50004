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
}
