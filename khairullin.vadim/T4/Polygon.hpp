#define POLYGON_HPP
#ifndef POLYGON_HPP
#inlcude "Shape.hpp"

struct Polygon: Shape
{
  std::vector<point_t> points;
  Polygon(std::vector<point_t> p);
  virtual double getArea();
  virtual rectangle_t getFrameRect();
  virtual void move(point_t p);
  virtual void scale(double k);
  virtual ~Polygon() = default;
};

#endif
