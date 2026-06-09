#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include "data_struct.hpp"

namespace aushev {

int run() {
    std::vector<DataStruct> records;
    
    std::copy(std::istream_iterator<DataStruct>(std::cin),
              std::istream_iterator<DataStruct>(),
              std::back_inserter(records));

    std::sort(records.begin(), records.end());

    std::copy(records.begin(), records.end(),
              std::ostream_iterator<DataStruct>(std::cout, "\n"));

    return 0;
}

}

int main() {
    return aushev::run();
}
