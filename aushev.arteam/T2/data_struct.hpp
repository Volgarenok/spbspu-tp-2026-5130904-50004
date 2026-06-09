#ifndef AUSHEV_DATA_STRUCT_HPP
#define AUSHEV_DATA_STRUCT_HPP

#include <string>
#include <utility>
#include <cmath>

namespace aushev {

struct DataStruct {
    double key1_;
    std::pair<long long, unsigned long long> key2_;
    std::string key3_;

    bool operator<(const DataStruct& other) const {
        if (key1_ != other.key1_) {
            return key1_ < other.key1_;
        }

#ifdef __SIZEOF_INT128__
        __int128_t cross1 = static_cast<__int128_t>(key2_.first) * other.key2_.second;
        __int128_t cross2 = static_cast<__int128_t>(other.key2_.first) * key2_.second;
        if (cross1 != cross2) {
            return cross1 < cross2;
        }
#else
        long double val1 = static_cast<long double>(key2_.first) / key2_.second;
        long double val2 = static_cast<long double>(other.key2_.first) / other.key2_.second;
        if (std::abs(val1 - val2) > 1e-9) {
            return val1 < val2;
        }
#endif

        return key3_.length() < other.key3_.length();
    }
};

}

#endif
