#ifndef IOGUARD_H
#define IOGUARD_H

#include "DataStruct.h"
#include <ios>

namespace nepochatova {
  class IOguard
  {
  public:
    explicit IOguard(std::basic_ios<char>& s);
    ~IOguard();
  private:
    std::basic_ios<char>& s_;
    std::streamsize precision_;
    std::streamsize width_;
    std::basic_ios<char>::fmtflags fmt_;
    char fill_;
  };
}

struct DelimiterIO {
  char expected_;
  char& last_;
};
std::istream& operator>>(std::istream& in, DelimiterIO&& dest);

struct LabelIO {
  std::string expected_;
};
std::istream& operator>>(std::istream& in, LabelIO&& dest);

#endif
