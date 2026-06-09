#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <iomanip>
#include <string>
#include <fstream>
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

    std::string cmd;
    while (std::cin >> cmd) {
        if (cmd == "AREA") {
            std::string sub;
            if (!(std::cin >> sub)) {
                std::cout << "<INVALID COMMAND>\n";
                continue;
            }
            if (sub == "EVEN") {
                double sum = 0.0;
                for (const auto& p : polygons) {
                    if (p.points_.size() % 2 == 0) {
                        sum += p.getArea();
                    }
                }
                std::cout << std::fixed << std::setprecision(1) << sum << "\n";
            } else if (sub == "ODD") {
                double sum = 0.0;
                for (const auto& p : polygons) {
                    if (p.points_.size() % 2 != 0) {
                        sum += p.getArea();
                    }
                }
                std::cout << std::fixed << std::setprecision(1) << sum << "\n";
            } else if (sub == "MEAN") {
                if (polygons.empty()) {
                    std::cout << "<INVALID COMMAND>\n";
                    continue;
                }
                double sum = 0.0;
                for (const auto& p : polygons) {
                    sum += p.getArea();
                }
                std::cout << std::fixed << std::setprecision(1) << (sum / polygons.size()) << "\n";
            } else {
                try {
                    size_t n = std::stoull(sub);
                    double sum = 0.0;
                    for (const auto& p : polygons) {
                        if (p.points_.size() == n) {
                            sum += p.getArea();
                        }
                    }
                    std::cout << std::fixed << std::setprecision(1) << sum << "\n";
                } catch (...) {
                    std::cout << "<INVALID COMMAND>\n";
                }
            }
        } else if (cmd == "MAX") {
            std::string sub;
            if (!(std::cin >> sub)) {
                std::cout << "<INVALID COMMAND>\n";
                continue;
            }
            if (polygons.empty()) {
                std::cout << "<INVALID COMMAND>\n";
                continue;
            }
            if (sub == "AREA") {
                double max_val = polygons[0].getArea();
                for (const auto& p : polygons) {
                    if (p.getArea() > max_val) {
                        max_val = p.getArea();
                    }
                }
                std::cout << std::fixed << std::setprecision(1) << max_val << "\n";
            } else if (sub == "VERTEXES") {
                size_t max_val = polygons[0].points_.size();
                for (const auto& p : polygons) {
                    if (p.points_.size() > max_val) {
                        max_val = p.points_.size();
                    }
                }
                std::cout << max_val << "\n";
            } else {
                std::cout << "<INVALID COMMAND>\n";
            }
        } else if (cmd == "MIN") {
            std::string sub;
            if (!(std::cin >> sub)) {
                std::cout << "<INVALID COMMAND>\n";
                continue;
            }
            if (polygons.empty()) {
                std::cout << "<INVALID COMMAND>\n";
                continue;
            }
            if (sub == "AREA") {
                double min_val = polygons[0].getArea();
                for (const auto& p : polygons) {
                    if (p.getArea() < min_val) {
                        min_val = p.getArea();
                    }
                }
                std::cout << std::fixed << std::setprecision(1) << min_val << "\n";
            } else if (sub == "VERTEXES") {
                size_t min_val = polygons[0].points_.size();
                for (const auto& p : polygons) {
                    if (p.points_.size() < min_val) {
                        min_val = p.points_.size();
                    }
                }
                std::cout << min_val << "\n";
            } else {
                std::cout << "<INVALID COMMAND>\n";
            }
        } else if (cmd == "COUNT") {
            std::string sub;
            if (!(std::cin >> sub)) {
                std::cout << "<INVALID COMMAND>\n";
                continue;
            }
            size_t count = 0;
            if (sub == "EVEN") {
                for (const auto& p : polygons) {
                    if (p.points_.size() % 2 == 0) {
                        ++count;
                    }
                }
                std::cout << count << "\n";
            } else if (sub == "ODD") {
                for (const auto& p : polygons) {
                    if (p.points_.size() % 2 != 0) {
                        ++count;
                    }
                }
                std::cout << count << "\n";
            } else {
                try {
                    size_t n = std::stoull(sub);
                    for (const auto& p : polygons) {
                        if (p.points_.size() == n) {
                            ++count;
                        }
                    }
                    std::cout << count << "\n";
                } catch (...) {
                    std::cout << "<INVALID COMMAND>\n";
                }
            }
        } else {
            std::cout << "<INVALID COMMAND>\n";
        }
    }

    return 0;
}

}

int main(int argc, const char* argv[]) {
    return aushev::run(argc, argv);
}
