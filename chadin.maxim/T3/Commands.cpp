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

  void processCommands(std::vector<Polygon>& polygons, std::istream& in, std::ostream& out)
  {
    using namespace std::placeholders;
    std::string cmd;
    while (in >> cmd) {
      if (cmd == "AREA") {
        std::string sub;
        if (!(in >> sub)) break;
        if (sub == "EVEN") {
          std::vector<Polygon> filtered;
          auto is_even = std::bind(std::equal_to<size_t>(),
                                   std::bind(std::modulus<size_t>(), std::bind(detail::getVertexes, _1), 2),
                                   0);
          std::copy_if(polygons.begin(), polygons.end(), std::back_inserter(filtered), is_even);
          std::vector<double> areas(filtered.size());
          std::transform(filtered.begin(), filtered.end(), areas.begin(), detail::getArea);
          double sum = std::accumulate(areas.begin(), areas.end(), 0.0);
          out << std::fixed << std::setprecision(1) << sum << '\n';
        } else if (sub == "ODD") {
          std::vector<Polygon> filtered;
          auto is_odd = std::bind(std::not_equal_to<size_t>(),
                                  std::bind(std::modulus<size_t>(), std::bind(detail::getVertexes, _1), 2),
                                  0);
          std::copy_if(polygons.begin(), polygons.end(), std::back_inserter(filtered), is_odd);
          std::vector<double> areas(filtered.size());
          std::transform(filtered.begin(), filtered.end(), areas.begin(), detail::getArea);
          double sum = std::accumulate(areas.begin(), areas.end(), 0.0);
          out << std::fixed << std::setprecision(1) << sum << '\n';
        } else if (sub == "MEAN") {
          if (polygons.empty()) {
            out << "<INVALID COMMAND>\n";
          } else {
            std::vector<double> areas(polygons.size());
            std::transform(polygons.begin(), polygons.end(), areas.begin(), detail::getArea);
            double sum = std::accumulate(areas.begin(), areas.end(), 0.0);
            out << std::fixed << std::setprecision(1) << sum / polygons.size() << '\n';
          }
        } else {
          try {
            const size_t n = std::stoull(sub);
            std::vector<Polygon> filtered;
            auto has_n = std::bind(std::equal_to<size_t>(), std::bind(detail::getVertexes, _1), n);
            std::copy_if(polygons.begin(), polygons.end(), std::back_inserter(filtered), has_n);
            std::vector<double> areas(filtered.size());
            std::transform(filtered.begin(), filtered.end(), areas.begin(), detail::getArea);
            double sum = std::accumulate(areas.begin(), areas.end(), 0.0);
            out << std::fixed << std::setprecision(1) << sum << '\n';
          } catch (...) {
            out << "<INVALID COMMAND>\n";
          }
        }
      } else if (cmd == "MAX") {
        std::string sub;
        if (!(in >> sub)) break;
        if (polygons.empty()) {
          out << "<INVALID COMMAND>\n";
        } else if (sub == "AREA") {
          auto cmp = std::bind(std::less<double>(), std::bind(detail::getArea, _1), std::bind(detail::getArea, _2));
          auto it = std::max_element(polygons.begin(), polygons.end(), cmp);
          out << std::fixed << std::setprecision(1) << detail::getArea(*it) << '\n';
        } else if (sub == "VERTEXES") {
          auto cmp = std::bind(std::less<size_t>(), std::bind(detail::getVertexes, _1), std::bind(detail::getVertexes, _2));
          auto it = std::max_element(polygons.begin(), polygons.end(), cmp);
          out << detail::getVertexes(*it) << '\n';
        } else {
          out << "<INVALID COMMAND>\n";
        }
      } else if (cmd == "MIN") {
        std::string sub;
        if (!(in >> sub)) break;
        if (polygons.empty()) {
          out << "<INVALID COMMAND>\n";
        } else if (sub == "AREA") {
          auto cmp = std::bind(std::less<double>(), std::bind(detail::getArea, _1), std::bind(detail::getArea, _2));
          auto it = std::min_element(polygons.begin(), polygons.end(), cmp);
          out << std::fixed << std::setprecision(1) << detail::getArea(*it) << '\n';
        } else if (sub == "VERTEXES") {
          auto cmp = std::bind(std::less<size_t>(), std::bind(detail::getVertexes, _1), std::bind(detail::getVertexes, _2));
          auto it = std::min_element(polygons.begin(), polygons.end(), cmp);
          out << detail::getVertexes(*it) << '\n';
        } else {
          out << "<INVALID COMMAND>\n";
        }
      } else if (cmd == "COUNT") {
        std::string sub;
        if (!(in >> sub)) break;
        if (sub == "EVEN") {
          auto is_even = std::bind(std::equal_to<size_t>(),
                                   std::bind(std::modulus<size_t>(), std::bind(detail::getVertexes, _1), 2),
                                   0);
          out << std::count_if(polygons.begin(), polygons.end(), is_even) << '\n';
        } else if (sub == "ODD") {
          auto is_odd = std::bind(std::not_equal_to<size_t>(),
                                  std::bind(std::modulus<size_t>(), std::bind(detail::getVertexes, _1), 2),
                                  0);
          out << std::count_if(polygons.begin(), polygons.end(), is_odd) << '\n';
        } else {
          try {
            const size_t n = std::stoull(sub);
            auto has_n = std::bind(std::equal_to<size_t>(), std::bind(detail::getVertexes, _1), n);
            out << std::count_if(polygons.begin(), polygons.end(), has_n) << '\n';
          } catch (...) {
            out << "<INVALID COMMAND>\n";
          }
        }
      } else if (cmd == "RMECHO") {
        Polygon target;
        if (in >> target) {
          auto is_echo = std::bind(std::logical_and<bool>(),
                                   std::bind(std::equal_to<Polygon>(), _1, _2),
                                   std::bind(std::equal_to<Polygon>(), _1, target));
          const size_t initial_size = polygons.size();
          auto it = std::unique(polygons.begin(), polygons.end(), is_echo);
          polygons.erase(it, polygons.end());
          out << initial_size - polygons.size() << '\n';
        } else {
          out << "<INVALID COMMAND>\n";
          in.clear();
        }
      } else if (cmd == "INFRAME") {
        Polygon target;
        if (in >> target) {
          if (polygons.empty()) {
            out << "<FALSE>\n";
          }
