#include <functional>
#include "Polygon.h"
#include <algorithm>
#include <numeric>
#include <fstream>
#include <iterator>
#include <map>
#include <sstream>
#include <iomanip>

namespace alekseev {
  using data_t = std::vector< Polygon >;
  using args_t = std::vector< std::string >;
  using const_command = std::function< double (const data_t &, const args_t &) >;

  double area(const data_t & data, const args_t & args);
  double extremum(const data_t & data, const args_t & args, bool max);
  double max(const data_t & data, const args_t & args);
  double min(const data_t & data, const args_t & args);
  double count(const data_t & data, const args_t & args);
  double rects(const data_t & data, const args_t & args);
  double intersections(const data_t & data, const args_t & args);
  std::map< std::string, const_command > cmds;
}

int main(int argc, char * argv[])
{
  if (argc != 2) {
    std::cerr << "Usage: " << argv[0] << " input_file\n";
    return 1;
  }
  std::ifstream ifs(argv[1]);
  if (!ifs) {
    std::cerr << "Error opening file " << argv[1] << "\n";
    return 1;
  }
  alekseev::data_t data;
  std::string line;
  while (std::getline(ifs, line)) {
    data.push_back(alekseev::from_string(line));
  }
  ifs.close();
  auto rem_it = std::remove_if(data.begin(), data.end(), [](const alekseev::Polygon & p) {
    return p.size() == 0;
  });
  data.erase(rem_it, data.end());
  std::string command;
  std::cout << std::fixed << std::setprecision(2);
  while (std::getline(std::cin, command)) {
    std::istringstream iss(command);
    std::string name;
    iss >> name;
    std::istream_iterator< std::string > b(iss), e{};
    alekseev::args_t args;
    std::copy(b, e, std::back_inserter(args));
    try {
      std::cout << alekseev::cmds.at(name)(data, args) << "\n";
    } catch (...) {
      std::cout << "<INVALID COMMAND>\n";
    }
  }
}

double alekseev::area(const data_t & data, const args_t & args)
{
  if (args.size() != 1) {
    throw std::invalid_argument("Wrong number of arguments");
  }
  if (args[0] == "EVEN" || args[0] == "ODD") {
    int odd = args[0] == "ODD";
    std::vector< Polygon > temp;
    std::copy_if(data.begin(), data.end(), std::back_inserter(temp), [odd](const Polygon & x) {
      return x.size() % 2 == odd;
    });
    return std::accumulate(temp.begin(), temp.end(), 0.0);
  } else if (args[0] == "MEAN") {
    if (data.empty()) {
      throw std::invalid_argument("Empty data");
    }
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
  if (data.empty()) {
    throw std::invalid_argument("Empty data");
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
    int odd = args[0] == "ODD";
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

double alekseev::rects(const data_t & data, const args_t & args)
{
  if (!args.empty()) {
    throw std::invalid_argument("Wrong number of arguments");
  }
  return std::count_if(data.begin(), data.end(), is_rectangle);
}

double alekseev::intersections(const data_t & data, const args_t & args)
{
  if (args.empty()) {
    throw std::invalid_argument("Wrong number of arguments");
  }
  Polygon p(args);
  return std::count_if(data.begin(), data.end(), [p](const Polygon & x) {
    return x.intersects(p);
  });
}
