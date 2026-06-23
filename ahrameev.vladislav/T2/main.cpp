#include <iostream>
#include <sstream>

#include "data_struct.h"

int main()
{
  std::istringstream iss("50.0d -89LL");
  double d = 0.0;
  long long ll = 0;
  iss >> d >> ll; 
  std::cout << "d=" << d << " ll=" << ll << "\n";
  return 0;
}