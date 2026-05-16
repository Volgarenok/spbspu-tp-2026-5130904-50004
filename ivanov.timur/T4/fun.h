
#ifndef FUN_H
#define FUN_H

#include "Rectangle.h"
#include "Circle.h"
#include "Polygon.h"
#include <iostream>
#include <memory>
#include <vector>

std::vector<double> get_areas(const std::vector<std::weak_ptr<Shape>> v) {
 std::vector<double> ans;
  for (const auto& wptr : v) {
    auto ptr = wptr.lock();
    if (ptr) {
      ans.push_back(ptr->getArea());
    } else {
      throw std::logic_error("Weak ptr disparaged");
    }
  }
  return ans;
}
double get_area(std::vector<double> v) {
  double ans = 0;
  for (const double& elem : v) {
    ans += elem;
  }
  return ans;
}
void output_areas(std::vector<double> areas) {
  for (size_t i = 0; i < areas.size(); ++i) {
    std::cout << "AREA OF OBJECT " << (i + 1) << ": " << areas[i] << "\n";
  }
  std::cout << "TOTAL AREA: " << get_area(areas) << "\n";
}

std::vector<rectangle_t> get_def_rects(std::vector<std::weak_ptr<Shape>> v) {
  std::vector<rectangle_t> ans;
  for (const auto& wptr : v) {
    auto ptr = wptr.lock();
    if (ptr) {
      ans.push_back(ptr->getFrameRect());
    } else {
      throw std::logic_error("Weak ptr disparaged");
    }
  }
  return ans;
}
rectangle_t get_rectangle(std::vector<rectangle_t> recs) {
  double left_x = recs[0].pos.x;
  double right_x = recs[0].pos.x;
  double down_y = recs[0].pos.y;
  double upper_y = recs[0].pos.y;

  for (size_t i = 1; i < recs.size(); ++i) {
    if (recs[i].pos.x < left_x) left_x = recs[i].pos.x;
    if (recs[i].pos.x > right_x) right_x = recs[i].pos.x;
    if (recs[i].pos.y < down_y) down_y = recs[i].pos.y;
    if (recs[i].pos.y > upper_y) upper_y = recs[i].pos.y;
  }

  return rectangle_t(right_x - left_x, upper_y - down_y, point_t(left_x, down_y));
}
void output_rect(rectangle_t rect) {
  std::cout << "RECTANGLE: (" << rect.width << ", " << rect.height << ")\n";
}
void output_rect(rectangle_t rect, size_t pos) {
  std::cout << "RECTANGLE " << (pos + 1) <<": (" << rect.width << ", " << rect.height << ")\n";
}
void output_def_rects(std::vector<rectangle_t> v) {
  for (size_t i = 0; i < v.size(); ++i) {
    output_rect(v[i], i);
  }
  output_rect(get_rectangle(v));
}

void recalculate_figures(std::vector<std::weak_ptr<Shape>> v, const double& k, const point_t& p) {
  for (const auto& wptr : v) {
    auto ptr = wptr.lock();
    if (ptr) {
      ptr->scale(p, k);
    } else {
      throw std::logic_error("Weak ptr disparaged");
    }
  }
  std::cout << "RECALCULATION...\n";
}

#endif
