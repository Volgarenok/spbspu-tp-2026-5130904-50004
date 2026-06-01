#ifndef DELIMITER_H
#define DELIMITER_H

#include <iostream>

namespace vasilenko
{
  struct DelimiterIO
  {
    char expected;
  };

  std::istream& operator>>(std::istream& in, DelimiterIO&& dest);
}

#endif
