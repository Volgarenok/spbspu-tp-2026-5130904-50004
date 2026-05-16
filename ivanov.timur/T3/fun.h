#ifndef FUN_H
#define FUN_H
#include "Polygon.h"
#include "IO.h"
#include <numeric>
#include <functional>
#include <algorithm>
using namespace std::placeholders;

inline double addIfParity(double sum, const Polygon& p, bool isEven) {
  return sum + (p.getVertexes() % 2 == isEven ? p.getArea() : 0.0);
}

inline double addIfVertexCount(double sum, const Polygon& p, size_t target) {
  return sum + (p.getVertexes() == target ? p.getArea() : 0.0);
}

inline bool isEvenVertexes(const Polygon& p) { return p.getVertexes() % 2 == 0; }
inline bool isOddVertexes(const Polygon& p) { return p.getVertexes() % 2 != 0; }
inline bool hasVertexCount(const Polygon& p, size_t n) { return p.getVertexes() == n; }

inline bool isSamePolygon(const Polygon& a, const Polygon& b) {
  if (a.getVertexes() != b.getVertexes()) return false;

  const auto& ptsA = a.getPoints();
  const auto& ptsB = b.getPoints();

  auto dxA = ptsA[0].x, dyA = ptsA[0].y;
  auto dxB = ptsB[0].x, dyB = ptsB[0].y;

  for (size_t i = 0; i < ptsA.size(); ++i) {
    if ((ptsA[i].x - dxA) != (ptsB[i].x - dxB) ||
        (ptsA[i].y - dyA) != (ptsB[i].y - dyB))
      return false;
  }
  return true;
}

inline bool hasRightAngle(const Polygon& p) {
  const auto& pts = p.getPoints();
  size_t n = pts.size();
  if (n < 3) return false;
  for (size_t i = 0; i < n; ++i) {
    size_t prev = (i == 0) ? n - 1 : i - 1;
    size_t next = (i + 1) % n;
    long long v1x = pts[prev].x - pts[i].x;
    long long v1y = pts[prev].y - pts[i].y;
    long long v2x = pts[next].x - pts[i].x;
    long long v2y = pts[next].y - pts[i].y;
    if (v1x * v2x + v1y * v2y == 0) return true;
  }
  return false;
}

namespace ivanov{

inline double area(const std::vector<Polygon>& fts, bool isEven) {
  auto accumulator = std::bind(addIfParity, _1, _2, isEven);
  return std::accumulate(fts.begin(), fts.end(), 0.0, accumulator);
}

inline double area(const std::vector<Polygon>& fts, const std::string& param) {
  if (param == "MEAN") {
    if (fts.empty()) return 0.0;
    auto accumulator = std::bind(std::plus<double>(), _1,
                                 std::bind(&Polygon::getArea, _2));
    double sum = std::accumulate(fts.begin(), fts.end(), 0.0, accumulator);
    return sum / fts.size();
  } else if (param == "EVEN") {
    return area(fts, false);
  } else if (param == "ODD") {
    return area(fts, true);
  } else {
    size_t n;
    try {
      n = std::stoull(param);
    } catch (...) {
      return 0.0;
    }
    return area(fts, n);
  }
}

inline double area(const std::vector<Polygon>& fts, size_t vertexes_amn) {
  auto accumulator = std::bind(addIfVertexCount, _1, _2, vertexes_amn);
  return std::accumulate(fts.begin(), fts.end(), 0.0, accumulator);
}

inline size_t count(const std::vector<Polygon>& fts, size_t num) {
  return std::count_if(fts.begin(), fts.end(),
                       std::bind(hasVertexCount, _1, num));
}

inline double max(const std::vector<Polygon>& fts, const std::string& param) {
  if (fts.empty()) return 0.0;
  if (param == "AREA") {
    auto comp = std::bind(std::less<double>(),
                          std::bind(&Polygon::getArea, _1),
                          std::bind(&Polygon::getArea, _2));
    return std::max_element(fts.begin(), fts.end(), comp)->getArea();
  } else if (param == "VERTEXES") {
    auto comp = std::bind(std::less<size_t>(),
                          std::bind(&Polygon::getVertexes, _1),
                          std::bind(&Polygon::getVertexes, _2));
    return static_cast<double>(
        std::max_element(fts.begin(), fts.end(), comp)->getVertexes());
  }
  return 0.0;
}

inline double min(const std::vector<Polygon>& fts, const std::string& param) {
  if (fts.empty()) return 0.0;
  if (param == "AREA") {
    auto comp = std::bind(std::less<double>(),
                          std::bind(&Polygon::getArea, _1),
                          std::bind(&Polygon::getArea, _2));
    return std::min_element(fts.begin(), fts.end(), comp)->getArea();
  } else if (param == "VERTEXES") {
    auto comp = std::bind(std::less<size_t>(),
                          std::bind(&Polygon::getVertexes, _1),
                          std::bind(&Polygon::getVertexes, _2));
    return static_cast<double>(
        std::min_element(fts.begin(), fts.end(), comp)->getVertexes());
  }
  return 0.0;
}

inline size_t count(const std::vector<Polygon>& fts, const std::string& param) {
  if (param == "EVEN") {
    return std::count_if(fts.begin(), fts.end(),
                         std::bind(isEvenVertexes, _1));
  } else if (param == "ODD") {
    return std::count_if(fts.begin(), fts.end(),
                         std::bind(isOddVertexes, _1));
  }
  return 0;
}

inline size_t same(const std::vector<Polygon>& fts, const Polygon& target) {
  return std::count_if(fts.begin(), fts.end(),
                       std::bind(isSamePolygon, _1, target));
}

inline size_t rightshapes(const std::vector<Polygon>& fts) {
  return std::count_if(fts.begin(), fts.end(), hasRightAngle);
}

}

#endif
