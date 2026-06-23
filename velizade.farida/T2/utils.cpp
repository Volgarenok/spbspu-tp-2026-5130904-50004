#include "utils.hpp"
#include <cctype>
#include <string>

velizade::StreamGuard::StreamGuard(std::ios& stream):
    stream_(stream),
    precision_(stream.precision()),
    width_(stream.width()),
    flags_(stream.flags()),
    fill_(stream.fill())
{}

velizade::StreamGuard::~StreamGuard()
{
  stream_.precision(precision_);
  stream_.width(width_);
  stream_.flags(flags_);
  stream_.fill(fill_);
}

std::istream& velizade::operator>>(std::istream& in, velizade::DecLiteral& num)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }

  velizade::StreamGuard guard(in);
  std::string token;
  in >> token;
  if (!in)
  {
    return in;
  }

  if (token.size() < 4)
  {
    in.setstate(std::ios::failbit);
    return in;
  }
  std::string suffix = token.substr(token.size() - 3);
  for (char& c : suffix)
  {
    c = std::tolower(static_cast<unsigned char>(c));
  }
  if (suffix != "ull")
  {
    in.setstate(std::ios::failbit);
    return in;
  }

  std::string digits = token.substr(0, token.size() - 3);
  if (digits.empty() || digits.find_first_not_of("0123456789") != std::string::npos)
  {
    in.setstate(std::ios::failbit);
    return in;
  }

  try
  {
    num.value = std::stoull(digits);
  }
  catch (...)
  {
    in.setstate(std::ios::failbit);
  }
  return in;
}

std::ostream& velizade::operator<<(std::ostream& out, const velizade::DecLiteral& num)
{
  velizade::StreamGuard guard(out);
  out << num.value << "ull";
  return out;
}

bool velizade::operator<(const velizade::DecLiteral& a, const velizade::DecLiteral& b)
{
  return a.value < b.value;
}

bool velizade::operator==(const velizade::DecLiteral& a, const velizade::DecLiteral& b)
{
  return a.value == b.value;
}

std::istream& velizade::operator>>(std::istream& in, velizade::HexLiteral& num)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }

  velizade::StreamGuard guard(in);
  std::string token;
  in >> token;
  if (!in)
  {
    return in;
  }

  if (token.size() < 3 || token[0] != '0' || (token[1] != 'x' && token[1] != 'X'))
  {
    in.setstate(std::ios::failbit);
    return in;
  }

  std::string hexPart = token.substr(2);
  if (hexPart.empty() || hexPart.find_first_not_of("0123456789abcdefABCDEF") != std::string::npos)
  {
    in.setstate(std::ios::failbit);
    return in;
  }

  try
  {
    num.value = std::stoull(hexPart, nullptr, 16);
  }
  catch (...)
  {
    in.setstate(std::ios::failbit);
  }
  return in;
}

std::ostream& velizade::operator<<(std::ostream& out, const velizade::HexLiteral& num)
{
  velizade::StreamGuard guard(out);
  out << "0x" << std::hex << std::nouppercase << num.value << std::dec;
  return out;
}

bool velizade::operator<(const velizade::HexLiteral& a, const velizade::HexLiteral& b)
{
  return a.value < b.value;
}

bool velizade::operator==(const velizade::HexLiteral& a, const velizade::HexLiteral& b)
{
  return a.value == b.value;
}

bool velizade::readExpectedChar(std::istream& in, char expected)
{
  char c;
  in >> c;
  if (c != expected)
  {
    in.setstate(std::ios::failbit);
    return false;
  }
  return true;
}
