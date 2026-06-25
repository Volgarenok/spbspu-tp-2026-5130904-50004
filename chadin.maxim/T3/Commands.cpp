#include "Commands.hpp"
#include <algorithm>
#include <numeric>
#include <functional>
#include <iomanip>
#include <string>

namespace chadin {
  namespace detail {

    struct multiply_cross
    {
      double operator()(const Point& a, const Point& b) const
      {
        return static_cast<double>(a.x) * b.y - static_cast<double>(a.y) * b.x;
      }
    };

    struct compare_x
    {
      bool operator()(const Point& a, const Point& b) const { return a.x < b.x; }
    };

    struct compare_y
    {
      bool operator()(const Point& a, const Point& b) const { return a.y < b.y; }
    };

    double getArea(const Polygon& p)
    {
      if (p.points.size() < 3) {
        return 0.0;
      }
      std::vector<double> products(p.points.size());
      std::vector<Point> shifted(p.points.size());
      std::copy(p.points.begin() + 1, p.points.end(), shifted.begin());
      shifted.back() = p.points.front();
      std::transform(p.points.begin(), p.points.end(), shifted.begin(), products.begin(), multiply_cross());

      double sum = std::accumulate(products.begin(), products.end(), 0.0);
      return std::abs(sum) / 2.0;
    }

    size_t getVertexes(const Polygon& p)
    {
      return p.points.size();
    }

    int getMinX(const Polygon& p)
    {
      return std::min_element(p.points.begin(), p.points.end(), compare_x())->x;
    }

    int getMaxX(const Polygon& p)
    {
      return std::max_element(p.points.begin(), p.points.end(), compare_x())->x;
    }

    int getMinY(const Polygon& p)
    {
      return std::min_element(p.points.begin(), p.points.end(), compare_y())->y;
    }

    int getMaxY(const Polygon& p)
    {
      return std::max_element(p.points.begin(), p.points.end(), compare_y())->y;
    }

  }
