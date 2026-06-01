#ifndef SUBTYPES_HPP
#define SUBTYPES_HPP

#include <iostream>
#include <string>

namespace vasilenko {

  struct StreamGuard {
    explicit StreamGuard(std::basic_ios<char>& s);
    ~StreamGuard();
  private:
    std::basic_ios<char>& s_;
    std::streamsize precision_;
    std::streamsize width_;
    std::ios_base::fmtflags flags_;
    char fill_;
  };

  struct DelimiterI {
    char exp;
  };
  std::istream& operator>>(std::istream& in, DelimiterI&& dest);

  struct DoubleSciI {
    double& ref;
  };
  std::istream& operator>>(std::istream& in, DoubleSciI&& dest);

  struct DoubleSciO {
    double val;
  };
  std::ostream& operator<<(std::ostream& out, const DoubleSciO& dest);

  struct SignedLongLongI {
    long long& ref;
  };
  std::istream& operator>>(std::istream& in, SignedLongLongI&& dest);

  struct SignedLongLongO {
    long long val;
  };
  std::ostream& operator<<(std::ostream& out, const SignedLongLongO& dest);

  struct StringI {
    std::string& ref;
  };
  std::istream& operator>>(std::istream& in, StringI&& dest);

  struct StringO {
    std::string val;
  };
  std::ostream& operator<<(std::ostream& out, const StringO& dest);

}

#endif
