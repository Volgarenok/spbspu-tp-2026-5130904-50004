#include <iostream>
#include <sstream>

#include "data_struct.h"

int main()
{
  std::istringstream iss("(:");
  char c1 = '\0', c2 = '\0';
  iss >> c1 >> c2;
  std::cout << "Read: '" << c1 << "' '" << c2 << "'\n";
}