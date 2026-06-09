#ifndef AUSHEV_DATA_STRUCT_HPP
#define AUSHEV_DATA_STRUCT_HPP

#include <string>
#include <utility>
#include <cmath>
#include <iostream>

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

inline std::istream& operator>>(std::istream& is, DataStruct& data) {
    while (true) {
        char ch;
        while (is.get(ch)) {
            if (ch == '(') {
                is.get(ch);
                if (ch == ':') {
                    break;
                }
            }
        }
        if (!is) {
            return is;
        }

        bool has_k1 = false;
        bool has_k2 = false;
        bool has_k3 = false;
        bool valid = true;

        while (is >> std::ws) {
            is.get(ch);
            if (ch == ':') {
                is.get(ch);
                if (ch == ')') {
                    break;
                }
                is.putback(ch);
            } else {
                is.putback(ch);
            }

            std::string key;
            is >> key;

            if (key.length() >= 2 && key.substr(0, 2) == "(:") {
                key = key.substr(2);
            }
            if (!key.empty() && key.back() == ':') {
                key.pop_back();
            }

            if (key == "key1") {
                if (!(is >> data.key1_)) {
                    valid = false;
                } else {
                    has_k1 = true;
                }
            } else if (key == "key2") {
                char p1, c1, n_ch, c2, d_ch, c3, p2;
                if (is >> p1 >> c1 >> n_ch >> data.key2_.first >> c2 >> d_ch >> data.key2_.second >> c3 >> p2) {
                    if (p1 == '(' && c1 == ':' && n_ch == 'N' && c2 == ':' && d_ch == 'D' && c3 == ':' && p2 == ')') {
                        has_k2 = true;
                    } else {
                        valid = false;
                    }
                } else {
                    valid = false;
                }
            } else if (key == "key3") {
                is >> std::ws;
                is.get(ch);
                if (ch == '"') {
                    std::string val;
                    while (is.get(ch) && ch != '"') {
                        if (ch == '\\') {
                            char next_ch;
                            if (is.get(next_ch)) {
                                val += next_ch;
                            }
                        } else {
                            val += ch;
                        }
                    }
                    data.key3_ = val;
                    has_k3 = true;
                } else {
                    valid = false;
                }
            } else {
                valid = false;
            }

            if (!valid) {
                break;
            }
        }

        if (valid && has_k1 && has_k2 && has_k3) {
            return is;
        }

        while (is.get(ch) && ch != '\n' && ch != ')') {}
    }
}

}

#endif
