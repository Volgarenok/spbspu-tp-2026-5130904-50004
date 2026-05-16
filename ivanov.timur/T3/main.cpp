#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string>
#include "Polygon.h"
#include "IO.h"
#include "fun.h"

using namespace ivanov;

int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <polygons_file>\n";
        return 1;
    }

    std::ifstream file(argv[1]);
    if (!file) {
        std::cerr << "Bad input error\n";
        return 1;
    }

    std::vector<Polygon> data;
    std::string line;

    while (std::getline(file, line)) {
        std::istringstream iss(line);
        Polygon tmp;
        if (iss >> tmp) {
            iss >> std::ws;
            if (iss.eof() && tmp.getVertexes() >= 3) {
                data.push_back(std::move(tmp));
            }
        }
    }

    while (std::getline(std::cin, line)) {
        if (line.empty()) continue;
        std::istringstream iss(line);
        std::string cmd;
        iss >> cmd;

        if (cmd == "AREA") {
            std::string param;
            if (!(iss >> param)) {
                std::cout << "<INVALID COMMAND>\n";
                continue;
            }
            if (param == "MEAN") {
                if (data.empty()) {
                    std::cout << "<INVALID COMMAND>\n";
                } else {
                    double res = area(data, std::string("MEAN"));
                    std::cout << std::fixed << std::setprecision(1) << res << "\n";
                }
            } else if (param == "EVEN" || param == "ODD") {
                double res = area(data, param);
                std::cout << std::fixed << std::setprecision(1) << res << "\n";
            } else {
                std::istringstream ps(param);
                size_t n;
                if (ps >> n && ps.eof()) {
                    if (n < 3) {
                        std::cout << "<INVALID COMMAND>\n";
                    } else {
                        double res = area(data, n);
                        std::cout << std::fixed << std::setprecision(1) << res << "\n";
                    }
                } else {
                    std::cout << "<INVALID COMMAND>\n";
                }
            }
        }
        else if (cmd == "MAX" || cmd == "MIN") {
            std::string type;
            if (!(iss >> type) || (type != "AREA" && type != "VERTEXES")) {
                std::cout << "<INVALID COMMAND>\n";
                continue;
            }
            if (data.empty()) {
                std::cout << "<INVALID COMMAND>\n";
                continue;
            }
            if (type == "AREA") {
                double res = (cmd == "MAX") ? max(data, type) : min(data, type);
                std::cout << std::fixed << std::setprecision(1) << res << "\n";
            } else {
                double res = (cmd == "MAX") ? max(data, type) : min(data, type);
                std::cout << static_cast<size_t>(res) << "\n";
            }
        }
        else if (cmd == "COUNT") {
            std::string param;
            if (!(iss >> param)) {
                std::cout << "<INVALID COMMAND>\n";
                continue;
            }
            if (param == "EVEN" || param == "ODD") {
                size_t res = count(data, param);
                std::cout << res << "\n";
            } else {
                std::istringstream ps(param);
                size_t n;
                if (ps >> n && ps.eof()) {
                    if (n < 3) {
                        std::cout << "<INVALID COMMAND>\n";
                    } else {
                        size_t res = count(data, n);
                        std::cout << res << "\n";
                    }
                } else {
                    std::cout << "<INVALID COMMAND>\n";
                }
            }
        }
        else if (cmd == "SAME") {
            Polygon target;
            if (iss >> target) {
                iss >> std::ws;
                if (iss.eof() && target.getVertexes() >= 3) {
                    size_t res = same(data, target);
                    std::cout << res << "\n";
                } else {
                    std::cout << "<INVALID COMMAND>\n";
                }
            } else {
                std::cout << "<INVALID COMMAND>\n";
            }
        }
        else if (cmd == "RIGHTSHAPES") {
            size_t res = rightshapes(data);
            std::cout << res << "\n";
        }
        else {
            std::cout << "<INVALID COMMAND>\n";
        }
    }
}
