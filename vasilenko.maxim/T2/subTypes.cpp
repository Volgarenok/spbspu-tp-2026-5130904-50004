#include "subTypes.hpp"
#include <cctype>

namespace vasilenko {

  StreamGuard::StreamGuard(std::basic_ios<char>& s) :
    s_(s),
    precision_(s.precision()),
    width_(s.width()),
    flags_(s.flags()),
    fill_(s.fill())
  {}

  StreamGuard::~StreamGuard() {
    s_.precision(precision_);
    s_.width(width_);
    s_.flags(flags_);
    s_.fill(fill_);
  }

  std::istream& operator>>(std::istream& in, DelimiterI&& dest) {
    std::istream::sentry sentry(in);
    if (!sentry) {
      return in;
    }
    char c = '0';
    in >> c;
    if (in && c != dest.exp) {
      in.setstate(std::ios::failbit);
    }
    return in;
  }

  std::istream& operator>>(std::istream& in, DoubleSciI&& dest) {
    std::istream::sentry sentry(in);
    if (!sentry) {
      return in;
    }
    in >> dest.ref;
    return in;
  }

  std::ostream& operator<<(std::ostream& out, const DoubleSciO& dest) {
    std::ostream::sentry sentry(out);
    if (!sentry) {
      return out;
    }
    StreamGuard guard(out);
    out << std::scientific << std::nouppercase << dest.val;
    return out;
  }

  std::istream& operator>>(std::istream& in, SignedLongLongI&& dest) {
    std::istream::sentry sentry(in);
    if (!sentry) {
      return in;
    }
    in >> dest.ref;
    char l1 = '0', l2 = '0';
    in >> l1 >> l2;
    if (!in || std::tolower(l1) != 'l' || std::tolower(l2) != 'l') {
      in.setstate(std::ios::failbit);
    }
    return in;
  }

  std::ostream& operator<<(std::ostream& out, const SignedLongLongO& dest) {
    std::ostream::sentry sentry(out);
    if (!sentry) {
      return out;
    }
    out << dest.val << "ll";
    return out;
  }

  std::istream& operator>>(std::istream& in, StringI&& dest) {
    std::istream::sentry sentry(in);
    if (!sentry) {
      return in;
    }
    char c = '0';
    in >> c;
    if (c != '"') {
      in.setstate(std::ios::failbit);
      return in;
    }
    std::string temp;
    std::getline(in, temp, '"');
    if (in) {
      dest.ref = temp;
    }
    return in;
  }

  std::ostream& operator<<(std::ostream& out, const StringO& dest) {
    std::ostream::sentry sentry(out);
    if (!sentry) {
      return out;
    }
    out << '"' << dest.val << '"';
    return out;
  }

}
