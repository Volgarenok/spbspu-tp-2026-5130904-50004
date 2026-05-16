#include <algorithm>
#include <iostream>
#include <iterator>
#include <sstream>
#include <vector>

namespace ivanov {
  struct DataStruct {
    long long key1;
    std::pair<long long, unsigned long long> key2;
    std::string key3;
  };

  struct DelimiterIO {
    char exp;
  };

  struct StringIO {
    std::string &ref;
  };

  struct LongIO {
    long long &ref;
  };

  struct PairIO {
    std::pair<long long, unsigned long long> &ref;
  };

  class IOGuard {
  public:
    explicit IOGuard(std::basic_ios<char> &s): s_(s), width_(s.width()), prc_(s.precision()),
                                               fmt_(s.flags()), fill_(s.fill()) {
    }

    ~IOGuard() {
      s_.width(width_);
      s_.fill(fill_);
      s_.precision(prc_);
      s_.flags(fmt_);
    }

  private:
    std::basic_ios<char> &s_;
    std::streamsize width_;
    std::streamsize prc_;
    std::basic_ios<char>::fmtflags fmt_;
    char fill_;
  };

  std::istream &operator>>(std::istream &in, DelimiterIO &&dest) {
    std::istream::sentry sentry(in);
    if (!sentry) return in;
    char c = 0;
    in >> c;
    if (in && c != dest.exp) in.setstate(std::ios::failbit);
    return in;
  }

  std::istream &operator>>(std::istream &in, StringIO &&dest) {
    std::istream::sentry sentry(in);
    if (!sentry) return in;
    char q;
    in >> q;
    if (!in || q != '"') {
      in.setstate(std::ios::failbit);
      return in;
    }
    std::string str;
    std::getline(in, str, '"');
    if (!in) return in;
    dest.ref = std::move(str);
    return in;
  }

  std::istream &operator>>(std::istream &in, LongIO &&dest) {
    std::istream::sentry sentry(in);
    if (!sentry) return in;
    long long val;
    in >> val;
    if (!in) return in;
    char s1, s2;
    in >> s1 >> s2;
    if (!in || (s1 != 'l' && s1 != 'L') || (s2 != 'L' && s2 != 'l')) {
      in.setstate(std::ios::failbit);
      return in;
    }
    dest.ref = val;
    return in;
  }

  std::istream &operator>>(std::istream &in, PairIO &&dest) {
    std::istream::sentry sentry(in);
    if (!sentry) return in;
    char c;

    in >> c;
    if (!in || c != '(') {
      in.setstate(std::ios::failbit);
      return in;
    }
    std::string token;
    in >> token;
    if (!in || token != ":N") {
      in.setstate(std::ios::failbit);
      return in;
    }

    long long n = 0;
    in >> n;
    if (!in) return in;

    in >> token;
    if (!in || token != ":D") {
      in.setstate(std::ios::failbit);
      return in;
    }

    unsigned long long d;
    in >> d;
    if (!in) return in;

    if (!(in >> DelimiterIO{':'} >> DelimiterIO{')'}))
    {
      return in;
    }

    dest.ref.first = n;
    dest.ref.second = d;
    return in;
  }

  std::istream &operator>>(std::istream &in, DataStruct &dest) {
    std::istream::sentry sentry(in);
    if (!sentry) return in;

    DataStruct input;
    bool hasKey1 = false, hasKey2 = false, hasKey3 = false;

    if (!(in >> DelimiterIO{'('})) return in;

    while (true) {
      in >> std::ws;
      if (!in) break;

      if (in.peek() == ')') {
        in.get();
        break;
      }
      if (!(in >> DelimiterIO{':'})) break;

      if (in.peek() == ')') {
        in.get();
        break;
      }

      std::string key;
      if (!(in >> key)) break;
      in >> std::ws;

      if (key == "key1") {
        if (hasKey1) {
          in.setstate(std::ios::failbit);
          break;
        }
        LongIO llio{input.key1};
        if (!(in >> std::move(llio))) break;
        hasKey1 = true;
      } else if (key == "key2") {
        if (hasKey2) {
          in.setstate(std::ios::failbit);
          break;
        }
        PairIO pio{input.key2};
        if (!(in >> std::move(pio))) break;
        hasKey2 = true;
      } else if (key == "key3") {
        if (hasKey3) {
          in.setstate(std::ios::failbit);
          break;
        }
        StringIO sio{input.key3};
        if (!(in >> std::move(sio))) break;
        hasKey3 = true;
      } else {
        in.setstate(std::ios::failbit);
        break;
      }
    }
    if (!in || !(hasKey1 && hasKey2 && hasKey3)) {
      in.setstate(std::ios::failbit);
      return in;
    }
    dest = std::move(input);
    return in;
  }

  std::ostream &operator<<(std::ostream &out, const DataStruct &src) {
    std::ostream::sentry sentry(out);
    if (!sentry) return out;

    IOGuard guard(out);
    out << "(:key1 " << src.key1 << "ll"
        << ":key2 (:N " << src.key2.first << ":D " << src.key2.second << ":)"
        << ":key3 \"" << src.key3 << "\":)";
    return out;
  }
}

using namespace ivanov;

int main() {
  std::vector<DataStruct> data;
  std::string line;

  while (std::getline(std::cin, line)) {
    std::istringstream iss(line);
    DataStruct tmp;
    if (iss >> tmp) {
      iss >> std::ws;
      if (iss.eof()) data.push_back(std::move(tmp));
    }
  }

  std::sort(data.begin(), data.end(), [](const DataStruct &a, const DataStruct &b) {
    if (a.key1 != b.key1) return a.key1 < b.key1;
    if (a.key2 != b.key2) return a.key2 < b.key2;
    return a.key3.length() < b.key3.length();
  });

  std::copy(data.begin(), data.end(), std::ostream_iterator<DataStruct>(std::cout, "\n"));
  return 0;
}
