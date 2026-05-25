#ifndef IOFMTGUARD_HPP
#define IOFMTGUARD_HPP

#include <ios>

namespace aydogan
{
  class IOFmtGuard
  {
  public:
    explicit IOFmtGuard(std::basic_ios< char >& stream);
    ~IOFmtGuard();

  private:
    std::basic_ios< char >& stream_;
    std::streamsize width_;
    std::streamsize precision_;
    std::basic_ios< char >::fmtflags flags_;
    char fill_;
  };
}

#endif
