#include <algorithm>
#include <cmath>
#include <complex>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <sstream>
#include <string>
#include <vector>

namespace em {

  struct IntLL {
    long long u = 0;
  };

  struct Complex {
    std::complex<double> c{0.0, 0.0};
  };

  struct DataStruct {
    IntLL key1{};
    Complex key2{};
    std::string key3{};

    DataStruct() = default;

    DataStruct(IntLL ll, Complex c, std::string s)
      : key1(ll),
        key2(c),
        key3(std::move(s)) {}
  };

  class IOGuard {
  public:
    explicit IOGuard(std::basic_ios<char>& s)
      : s_(s),
        width_(s.width()),
        precision_(s.precision()),
        fmtFlags_(s.flags()),
        fill_(s.fill()) {}

    ~IOGuard() {
      s_.width(width_);
      s_.precision(precision_);
      s_.flags(fmtFlags_);
      s_.fill(fill_);
    }

    IOGuard(const IOGuard&) = delete;
    IOGuard& operator=(const IOGuard&) = delete;

  private:
    std::basic_ios<char>& s_;
    std::streamsize width_;
    std::streamsize precision_;
    std::basic_ios<char>::fmtflags fmtFlags_;
    char fill_;
  };

  struct Delimiter {
    char expected;
  };

  std::istream& operator>>(std::istream& is, Delimiter&& d);
  std::istream& operator>>(std::istream& is, IntLL& u);
  std::istream& operator>>(std::istream& is, Complex& c);
  std::istream& operator>>(std::istream& is, DataStruct& d);

  std::ostream& operator<<(std::ostream& os, const IntLL& u);
  std::ostream& operator<<(std::ostream& os, const Complex& c);
  std::ostream& operator<<(std::ostream& os, const DataStruct& d);

  bool operator<(const IntLL& a, const IntLL& b);
  bool operator<(const Complex& a, const Complex& b);
  bool operator<(const DataStruct& a, const DataStruct& b);
  bool operator==(const DataStruct& a, const DataStruct& b);

  bool myLess(const DataStruct& d1, const DataStruct& d2);

}

std::istream& em::operator>>(std::istream& is, Delimiter&& d) {
  std::istream::sentry s(is);
  if (!s) {
    return is;
  }
  char c = 0;
  is >> c;
  if (is && (d.expected != c)) {
    is.setstate(std::ios::failbit);
  }
  return is;
}

std::istream& em::operator>>(std::istream& is, IntLL& u) {
  std::istream::sentry s(is);
  if (!s) {
    return is;
  }
  long long value = 0;
  is >> value;
  if (!is) {
    return is;
  }
  char c1 = 0;
  char c2 = 0;
  is >> c1 >> c2;
  if (!is) {
    return is;
  }
  const bool isValidSuffix = ((c1 == 'l') || (c1 == 'L')) &&
    ((c2 == 'l') || (c2 == 'L'));
  if (!isValidSuffix) {
    is.setstate(std::ios::failbit);
    return is;
  }
  u.u = value;
  return is;
}

std::istream& em::operator>>(std::istream& is, Complex& c) {
  std::istream::sentry s(is);
  if (!s) {
    return is;
  }
  char hash = 0;
  char letterC = 0;
  char openParen = 0;
  is >> hash >> letterC >> openParen;
  if (!is || (hash != '#') || (letterC != 'c') || (openParen != '(')) {
    is.setstate(std::ios::failbit);
    return is;
  }
  double real = 0.0;
  double imag = 0.0;
  is >> real >> imag;
  if (!is) {
    return is;
  }
  char closeParen = 0;
  is >> closeParen;
  if (!is || (closeParen != ')')) {
    is.setstate(std::ios::failbit);
    return is;
  }
  c.c = std::complex<double>(real, imag);
  return is;
}

std::istream& em::operator>>(std::istream& is, DataStruct& d) {
  std::istream::sentry s(is);
  if (!s) {
    return is;
  }
  while (is) {
    IOGuard guard(is);
    is >> std::noskipws;
    std::string line;
    std::getline(is, line);
    if (!is && line.empty()) {
      is.setstate(std::ios::failbit);
      return is;
    }
    if (line.size() < 4) {
      continue;
    }
    if ((line.substr(0, 2) != "(:") ||
      (line.substr(line.size() - 2) != ":)")) {
      continue;
    }
    const std::string content = line.substr(2, line.size() - 4);
    std::istringstream iss(content);
    iss >> std::noskipws;
    DataStruct temp{};
    bool hasKey1 = false;
    bool hasKey2 = false;
    bool hasKey3 = false;
    bool valid = true;
    while (iss && valid) {
      char ch = 0;
      while (iss >> ch &&
        ((ch == ' ') || (ch == '\t') || (ch == ':'))) {
      }
      if (!iss) {
        break;
      }
      std::string key;
      key += ch;
      while (iss >> ch && (ch != ' ')) {
        key += ch;
      }
      if ((key == "key1") && !hasKey1) {
        IntLL val{};
        iss >> val;
        if (iss) {
          temp.key1 = val;
          hasKey1 = true;
        } else {
          valid = false;
        }
      } else if ((key == "key2") && !hasKey2) {
        Complex val{};
        iss >> val;
        if (iss) {
          temp.key2 = val;
          hasKey2 = true;
        } else {
          valid = false;
        }
      } else if ((key == "key3") && !hasKey3) {
        char quote = 0;
        iss >> quote;
        if (quote == '"') {
          std::string val;
          while (iss >> ch && (ch != '"')) {
            val += ch;
          }
          if (iss) {
            temp.key3 = val;
            hasKey3 = true;
          } else {
            valid = false;
          }
        } else {
          valid = false;
        }
      } else {
        valid = false;
      }
    }
    if (valid && hasKey1 && hasKey2 && hasKey3) {
      d = temp;
      return is;
    }
  }
  is.setstate(std::ios::failbit);
  return is;
}

int main() {
  return 0;
}
