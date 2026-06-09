#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include "geometry.hpp"

namespace aushev {

int run(int argc, const char* argv[]) {
    if (argc < 2) {
        std::cerr << "Error: filename is required\n";
        return 1;
    }

    std::ifstream file(argv[1]);
    if (!file.is_open()) {
        std::cerr << "Error: cannot open file\n";
        return 1;
    }

    std::vector<Polygon> polygons;
    std::copy(std::istream_iterator<Polygon>(file),
              std::istream_iterator<Polygon>(),
              std::back_inserter(polygons));

    return 0;
}

}

int main(int argc, const char* argv[]) {
    return aushev::run(argc, argv);
}
