#include <iostream>
#include <memory>
#include <vector>
#include <algorithm>
#include <string>

#include "complexquad.hpp"
#include "rectangle.hpp"
#include "shape.hpp"
#include "triangle.hpp"

void scaleRelative(std::weak_ptr<vasilenko::Shape> weak_shape, const vasilenko::point_t &point, double coeff)
{
  std::shared_ptr<vasilenko::Shape> shape = weak_shape.lock();
  if (!shape) {
    throw std::runtime_error("Shape does not exist");
  }

  const vasilenko::rectangle_t initial_rect = shape->getFrameRect();
  shape->move(point);
  const vasilenko::rectangle_t rect_at_center = shape->getFrameRect();

  const double dx = (initial_rect.pos.x - rect_at_center.pos.x) * coeff;
  const double dy = (initial_rect.pos.y - rect_at_center.pos.y) * coeff;

  shape->scale(coeff);
  shape->move(dx, dy);
}

vasilenko::rectangle_t getTotalFrameRect(const std::vector<std::shared_ptr<vasilenko::Shape>> &shapes)
{
  if (shapes.empty()) {
    return {0.0, 0.0, {0.0, 0.0}};
  }

  const vasilenko::rectangle_t first = shapes[0]->getFrameRect();
  double min_x = first.pos.x - first.width / 2.0;
  double max_x = first.pos.x + first.width / 2.0;
  double min_y = first.pos.y - first.height / 2.0;
  double max_y = first.pos.y + first.height / 2.0;

  for (size_t i = 1; i < shapes.size(); ++i) {
    const vasilenko::rectangle_t r = shapes[i]->getFrameRect();
    min_x = std::min(min_x, r.pos.x - r.width / 2.0);
    max_x = std::max(max_x, r.pos.x + r.width / 2.0);
    min_y = std::min(min_y, r.pos.y - r.height / 2.0);
    max_y = std::max(max_y, r.pos.y + r.height / 2.0);
  }

  const double width = max_x - min_x;
  const double height = max_y - min_y;
  const vasilenko::point_t center = {min_x + width / 2.0, min_y + height / 2.0};

  return {width, height, center};
}

void printState(const std::vector<std::shared_ptr<vasilenko::Shape>> &shapes, const std::string &prefix)
{
  std::cout << "--- " << prefix << " ---\n";
  double total_area = 0.0;

  for (size_t i = 0; i < shapes.size(); ++i) {
    const double area = shapes[i]->getArea();
    total_area += area;
    const vasilenko::rectangle_t frame = shapes[i]->getFrameRect();

    std::cout << "Shape " << i + 1 << ":\n"
              << "  Area: " << area << "\n"
              << "  Frame: Width=" << frame.width
              << ", Height=" << frame.height
              << ", Center=(" << frame.pos.x << ", " << frame.pos.y << ")\n";
  }

  const vasilenko::rectangle_t total_frame = getTotalFrameRect(shapes);
  std::cout << "Total Area: " << total_area << "\n";
  std::cout << "Total Frame: Width=" << total_frame.width
            << ", Height=" << total_frame.height
            << ", Center=(" << total_frame.pos.x << ", " << total_frame.pos.y << ")\n\n";
}

int main()
{
  std::vector<std::shared_ptr<vasilenko::Shape>> shapes;

  try {
    shapes.push_back(std::make_shared<vasilenko::Rectangle>(10.0, 5.0, vasilenko::point_t{0.0, 0.0}));
    shapes.push_back(std::make_shared<vasilenko::Triangle>(
      vasilenko::point_t{-5.0, -5.0},
      vasilenko::point_t{5.0, -5.0},
      vasilenko::point_t{0.0, 5.0}
    ));
    shapes.push_back(std::make_shared<vasilenko::Complexquad>(
      vasilenko::point_t{-5.0, 5.0},
      vasilenko::point_t{5.0, -5.0},
      vasilenko::point_t{5.0, 5.0},
      vasilenko::point_t{-5.0, -5.0}
    ));
  } catch (const std::exception &e) {
    std::cerr << "Initialization error: " << e.what() << "\n";
    return 2;
  }

  double x = 0.0;
  double y = 0.0;
  double coeff = 0.0;

  std::cout << "Enter scaling point (X Y) and scale coefficient: ";
  if (!(std::cin >> x >> y >> coeff)) {
    std::cerr << "Input error: Invalid data format.\n";
    return 1;
  }

  if (coeff <= 0.0) {
    std::cerr << "Input error: Scale coefficient must be positive.\n";
    return 1;
  }

  printState(shapes, "BEFORE SCALING");

  try {
    for (auto &shape : shapes) {
      scaleRelative(shape, {x, y}, coeff);
    }
  } catch (const std::exception &e) {
    std::cerr << "Runtime error: " << e.what() << "\n";
    return 2;
  }

  printState(shapes, "AFTER SCALING");

  return 0;
}
