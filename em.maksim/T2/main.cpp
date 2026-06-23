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

int main() {
  return 0;
}
