#ifndef FORMATTERS_HPP
#define FORMATTERS_HPP

#include <iostream>
#include <string>
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

  struct DoubleLiteralIO
  {
    double& ref;
  };

  struct DoubleLiteralOut
  {
    double val;
  };

  struct UllHexIO
  {
    unsigned long long& ref;
  };

  struct UllHexOut
  {
    unsigned long long val;
  };

  struct StringIO
  {
    std::string& ref;
  };

  struct StringOut
  {
    const std::string& val;
  };

  std::istream& operator>>(std::istream& in, DelimiterIO&& dest);
  std::istream& operator>>(std::istream& in, DoubleLiteralIO&& dest);
  std::ostream& operator<<(std::ostream& out, const DoubleLiteralOut& dest);
  std::istream& operator>>(std::istream& in, UllHexIO&& dest);
  std::ostream& operator<<(std::ostream& out, const UllHexOut& dest);
  std::istream& operator>>(std::istream& in, StringIO&& dest);
  std::ostream& operator<<(std::ostream& out, const StringOut& dest);

}

#endif
