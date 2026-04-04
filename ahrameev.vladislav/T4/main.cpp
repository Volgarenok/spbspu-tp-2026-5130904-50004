#include "shape.hpp"
#include "rectangle.hpp"
#include "ellipse.hpp"
#include "rubber.hpp"
#include <iostream>
#include <vector>
#include <memory>
#include <string>

namespace akhrameev {

void printShapeInfo(const std::string& name, const Shape& s) {
    rectangle_t r = s.getFrameRect();
    std::cout << name << ":\n"
              << "  Area: " << s.getArea() << "\n"
              << "  FrameRect: w=" << r.width << ", h=" << r.height
              << ", center=(" << r.pos.x << ", " << r.pos.y << ")\n";
}

void printAll(const std::vector<std::shared_ptr<Shape>>& storage) {
    std::vector<std::weak_ptr<Shape>> weak_refs;
    for (const auto& sp : storage) weak_refs.push_back(sp);

    for (size_t i = 0; i < storage.size(); ++i) {
        if (auto sp = weak_refs[i].lock()) {
            printShapeInfo("Shape " + std::to_string(i + 1), *sp);
        }
    }
}

} 

int main() {
    using namespace akhrameev;

    std::vector<std::shared_ptr<Shape>> shapes;
    shapes.emplace_back(std::make_shared<Rectangle>(10.0, 5.0, point_t{0.0, 0.0}));
    shapes.emplace_back(std::make_shared<Ellipse>(4.0, 6.0, point_t{15.0, 0.0}));
    shapes.emplace_back(std::make_shared<Rubber>(
        point_t{-5.0, -5.0}, 2.0, point_t{-2.0, -2.0}, 6.0));

    std::cout << "BEFORE SCALING\n";
    printAll(shapes);

    return 0;
}