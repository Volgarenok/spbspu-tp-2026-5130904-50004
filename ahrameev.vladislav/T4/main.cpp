#include "shape.hpp"
#include "rectangle.hpp"
#include "ellipse.hpp"
#include "rubber.hpp"
#include <iostream>
#include <vector>
#include <memory>
#include <limits>
#include <algorithm>
#include <string>

namespace akhrameev {

void printShapeInfo(const std::string& name, const Shape& s) {
    rectangle_t r = s.getFrameRect();
    std::cout << name << ":\n"
              << "  Area: " << s.getArea() << "\n"
              << "  FrameRect: w=" << r.width << ", h=" << r.height
              << ", center=(" << r.pos.x << ", " << r.pos.y << ")\n";
}

double getTotalArea(const std::vector<std::weak_ptr<Shape>>& shapes) {
    double sum = 0.0;
    for (const auto& wp : shapes) if (auto sp = wp.lock()) sum += sp->getArea();
    return sum;
}

rectangle_t getOverallFrameRect(const std::vector<std::weak_ptr<Shape>>& shapes) {
    double min_x = std::numeric_limits<double>::max();
    double max_x = std::numeric_limits<double>::lowest();
    double min_y = std::numeric_limits<double>::max();
    double max_y = std::numeric_limits<double>::lowest();

    for (const auto& wp : shapes) {
        if (auto sp = wp.lock()) {
            rectangle_t r = sp->getFrameRect();
            min_x = std::min(min_x, r.pos.x - r.width / 2.0);
            max_x = std::max(max_x, r.pos.x + r.width / 2.0);
            min_y = std::min(min_y, r.pos.y - r.height / 2.0);
            max_y = std::max(max_y, r.pos.y + r.height / 2.0);
        }
    }
    return {max_x - min_x, max_y - min_y, {(min_x + max_x) / 2.0, (min_y + max_y) / 2.0}};
}

void scaleAllRelativeToPoint(std::vector<std::weak_ptr<Shape>>& shapes, point_t pivot, double factor) {
    for (auto& wp : shapes) {
        if (auto sp = wp.lock()) {
            point_t old = sp->getFrameRect().pos;
            sp->move(pivot.x - old.x, pivot.y - old.y);
            sp->scale(factor);
            sp->move(old.x - pivot.x, old.y - pivot.y);
        }
    }
}

void printAll(const std::vector<std::shared_ptr<Shape>>& storage) {
    std::vector<std::weak_ptr<Shape>> weak_refs;
    for (const auto& sp : storage) weak_refs.push_back(sp);

    for (size_t i = 0; i < storage.size(); ++i)
        if (auto sp = weak_refs[i].lock()) printShapeInfo("Shape " + std::to_string(i + 1), *sp);

    std::cout << "Total Area: " << getTotalArea(weak_refs) << "\n";
    rectangle_t ov = getOverallFrameRect(weak_refs);
    std::cout << "Overall FrameRect: w=" << ov.width << ", h=" << ov.height
              << ", center=(" << ov.pos.x << ", " << ov.pos.y << ")\n";
}

} 

int main() {
    using namespace akhrameev;

    std::vector<std::shared_ptr<Shape>> shapes;
    shapes.emplace_back(std::make_shared<Rectangle>(10.0, 5.0, point_t{0.0, 0.0}));
    shapes.emplace_back(std::make_shared<Ellipse>(4.0, 6.0, point_t{15.0, 0.0}));
    shapes.emplace_back(std::make_shared<Rubber>(
        point_t{-5.0, -5.0}, 2.0, point_t{-2.0, -2.0}, 6.0));

    const point_t pivot{0.0, 0.0};
    const double factor = 1.5;

    std::cout << "BEFORE SCALING\n";
    printAll(shapes);

    std::vector<std::weak_ptr<Shape>> weak_shapes;
    for (const auto& sp : shapes) weak_shapes.push_back(sp);
    scaleAllRelativeToPoint(weak_shapes, pivot, factor);

    std::cout << "\nAFTER SCALING (pivot: (" << pivot.x << ", " << pivot.y
              << "), factor: " << factor << ")\n";
    printAll(shapes);

    return 0;
}