#include <functional>
#include "Polygon.h"

namespace alekseev {
  using data_t = std::vector< Polygon >;
  using args_t = std::vector< std::string >;
  using command = std::function< double (data_t &, const args_t &) >;
  using const_command = std::function< double (const data_t &, const args_t &) >;

  double area(const data_t &, const args_t &);
  double max(const data_t &, const args_t &);
  double min(const data_t &, const args_t &);
  double count(const data_t &, const args_t &);
}

int main()
{
}
