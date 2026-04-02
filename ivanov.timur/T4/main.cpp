#include "fun.h"

int main() {
  std::cout.precision(2);
  std::vector<std::shared_ptr<Shape>> objs;

  objs.push_back(std::make_shared<Rectangle>(0, 0, 10, 15));
  objs.push_back(std::make_shared<Circle>(5, 5, 20));
  std::vector<point_t> v = {point_t(1, 0), point_t(1, 1), point_t(0, 0), point_t(0, 17)};
  objs.push_back(std::make_shared<Polygon>(v));

  try {
    output_areas(get_areas(std::vector<std::weak_ptr<Shape>>(objs.begin(), objs.end())));
    output_def_rects(get_def_rects(std::vector<std::weak_ptr<Shape>>(objs.begin(), objs.end())));
  } catch (...) {
    std::cerr << "Something went wrong\n";
    return 2;
  }

  double x, y, k;
  std::cin >> x >> y >> k;
  if (std::cin.fail() || std::cin.eof()) {
    std::cerr << "Bad input error\n";
    return 2;
  }

  try {
    recalculate_figures(std::vector<std::weak_ptr<Shape>>(objs.begin(), objs.end()), k, point_t(x, y));
  } catch (...) {
    std::cerr << "Recalculation went wrong\n";
    return 1;
  }

  try {
    output_areas(get_areas(std::vector<std::weak_ptr<Shape>>(objs.begin(), objs.end())));
    output_def_rects(get_def_rects(std::vector<std::weak_ptr<Shape>>(objs.begin(), objs.end())));
  } catch (...) {
    std::cerr << "Something went wrong\n";
    return 2;
  }

  return 0;
}
