#include <functional>
#include "Polygon.h"
#include <algorithm>
#include <numeric>

namespace alekseev {
  using data_t = std::vector< Polygon >;
  using args_t = std::vector< std::string >;
  using command = std::function< double (data_t &, const args_t &) >;
  using const_command = std::function< double (const data_t &, const args_t &) >;

  double area(const data_t & data, const args_t & args);
  double extremum(const data_t & data, const args_t & args, bool max);
  double max(const data_t & data, const args_t & args);
  double min(const data_t & data, const args_t & args);
  double count(const data_t & data, const args_t & args);
}

int main()
{
}

double alekseev::area(const data_t & data, const args_t & args)
{
  if (args.size() != 1) {
    throw std::invalid_argument("Wrong number of arguments");
  }
  if (args[0] == "EVEN" || args[0] == "ODD") {
    int odd = args[1] == "ODD";
    std::vector< Polygon > temp;
    std::copy_if(data.begin(), data.end(), std::back_inserter(temp), [odd](const Polygon & x) {
      return x.size() % 2 == odd;
    });
    return std::accumulate(data.begin(), data.end(), 0.0);
  } else if (args[0] == "MEAN") {
    double area = std::accumulate(data.begin(), data.end(), 0.0);
    return area / data.size();
  } else {
    try {
      size_t n = std::stoull(args[0]);
      data_t temp;
      std::copy_if(data.begin(), data.end(), std::back_inserter(temp), [n](const Polygon & x) {
        return x.size() == n;
      });
      return std::accumulate(temp.begin(), temp.end(), 0.0);
    } catch (...) {
      throw std::invalid_argument("Wrong argument");
    }
  }
}

double alekseev::extremum(const data_t & data, const args_t & args, bool max)
{
  if (args.size() != 1) {
    throw std::invalid_argument("Wrong number of arguments");
  }
  int k = max ? 1 : -1;
  if (args[0] == "AREA") {
    std::vector< double > squares;
    std::transform(data.begin(), data.end(), std::back_inserter(squares), [k](const Polygon & x) {
      return k * x.area();
    });
    return *std::max(squares.begin(), squares.end());
  } else if (args[0] == "VERTEXES") {
    std::vector< double > sizes;
    std::transform(data.begin(), data.end(), std::back_inserter(sizes), [k](const Polygon & x) {
      return k * x.size();
    });
    return *std::max(sizes.begin(), sizes.end());
  } else {
    throw std::invalid_argument("Wrong argument");
  }
}

double alekseev::max(const data_t & data, const args_t & args)
{
  return extremum(data, args, true);
}

double alekseev::min(const data_t & data, const args_t & args)
{
  return extremum(data, args, false);
}

double alekseev::count(const data_t & data, const args_t & args)
{
  if (args.size() != 1) {
    throw std::invalid_argument("Wrong number of arguments");
  }
  if (args[0] == "EVEN" || args[0] == "ODD") {
    int odd = args[1] == "ODD";
    return std::count_if(data.begin(), data.end(), [odd](const Polygon & x) {
      return x.size() % 2 == odd;
    });
  } else {
    try {
      size_t n = std::stoull(args[0]);
      return std::count_if(data.begin(), data.end(), [n](const Polygon & x) {
        return x.size() == n;
      });
    } catch (...) {
      throw std::invalid_argument("Wrong argument");
    }
  }
}
