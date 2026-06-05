#ifndef IO_UTILS_HPP
#define IO_UTILS_HPP
#include <istream>

namespace alberto {

struct ExpectChar
{
  char expected_ = '\0';
};
std::istream& operator>>(std::istream& in, ExpectChar ec);
struct ExpectStr
{
  const char* expected_ = nullptr;
};
std::istream& operator>>(std::istream& in, ExpectStr es);
}
#endif
