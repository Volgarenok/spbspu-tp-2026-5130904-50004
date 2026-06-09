#ifndef AUSHEV_GEOMETRY_HPP
#define AUSHEV_GEOMETRY_HPP

#include <vector>
#include <cmath>
#include <algorithm>
#include <iostream>
#include <string>

namespace aushev {

struct Point {
    int x_;
    int y_;

    bool operator==(const Point& other) const {
        return x_ == other.x_ && y_ == other.y_;
    }

    bool operator<(const Point& other) const {
        if (x_ != other.x_) {
            return x_ < other.x_;
        }
        return y_ < other.y_;
    }
};

struct Polygon {
    std::vector<Point> points_;

    double getArea() const {
        double area = 0.0;
        size_t n = points_.size();
        for (size_t i = 0; i < n; ++i) {
            size_t j = (i + 1) % n;
            area += points_[i].x_ * points_[j].y_ - points_[j].x_ * points_[i].y_;
        }
        return std::abs(area) / 2.0;
    }
};

inline std::istream& operator>>(std::istream& is, Polygon& poly) {
    std::string line;
    while (std::getline(is, line)) {
        size_t pos = 0;
        while (pos < line.size() && std::isspace(line[pos])) {
            ++pos;
        }
        if (pos == line.size()) {
            continue;
        }

        size_t n;
        size_t start = pos;
        while (pos < line.size() && !std::isspace(line[pos])) {
            ++pos;
        }
        try {
            n = std::stoull(line.substr(start, pos - start));
        } catch (...) {
            continue;
        }

        std::vector<Point> pts;
        bool valid = true;
        for (size_t i = 0; i < n; ++i) {
            while (pos < line.size() && std::isspace(line[pos])) {
                ++pos;
            }
            if (pos >= line.size() || line[pos] != '(') {
                valid = false;
                break;
            }
            ++pos;
            size_t p1 = pos;
            while (pos < line.size() && line[pos] != ';') {
                ++pos;
            }
            if (pos >= line.size()) {
                valid = false;
                break;
            }
            int x = std::stoi(line.substr(p1, pos - p1));
            ++pos;
            size_t p2 = pos;
            while (pos < line.size() && line[pos] != ')') {
                ++pos;
            }
            if (pos >= line.size()) {
                valid = false;
                break;
            }
            int y = std::stoi(line.substr(p2, pos - p2));
            ++pos;
            pts.push_back({x, y});
        }
        if (valid && pts.size() == n) {
            poly.points_ = std::move(pts);
            return is;
        }
    }
    is.setstate(std::ios::eofbit);
    return is;
}

inline std::ostream& operator<<(std::ostream& os, const Polygon& poly) {
    os << poly.points_.size();
    for (const auto& p : poly.points_) {
        os << " (" << p.x_ << ";" << p.y_ << ")";
    }
    os << "\n";
    return os;
}

}

#endif
