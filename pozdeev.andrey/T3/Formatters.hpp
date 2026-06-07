#ifndef FORMATTERS_HPP
#define FORMATTERS_HPP

#include <iostream>
#include <ios>

namespace pozdeev
{
  class IOGuard
  {
  public:
    explicit IOGuard(std::basic_ios< char >& s);
    ~IOGuard();

  private:
    std::basic_ios< char >& s_;
    std::ios_base::fmtflags flags_;
    std::streamsize precision_;
    std::basic_ios< char >::char_type fill_;
  };

  struct DelimiterIO
  {
    char exp;
  };

  std::istream& operator>>(std::istream& in, DelimiterIO&& dest);
}

#endif
