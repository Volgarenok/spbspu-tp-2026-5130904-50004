#include "shape.hpp"
#include "rectangle.hpp"
#include "ellipse.hpp"
#include "rubber.hpp"
#include <vector>
#include <memory>

namespace akhrameev {

void printAll(const std::vector<std::shared_ptr<Shape>>& storage) {
    (void)storage;
}

} 

int main() {
    using namespace akhrameev;

    std::vector<std::shared_ptr<Shape>> shapes;
    shapes.emplace_back(std::make_shared<Rectangle>(10.0, 5.0, point_t{0.0, 0.0}));
    shapes.emplace_back(std::make_shared<Ellipse>(4.0, 6.0, point_t{15.0, 0.0}));
    shapes.emplace_back(std::make_shared<Rubber>(
        point_t{-5.0, -5.0}, 2.0, point_t{-2.0, -2.0}, 6.0));

    return 0;
}