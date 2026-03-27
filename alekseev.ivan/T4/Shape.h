#ifndef SHAPE_H
#define SHAPE_H

struct point_t {
  double x, y;
};

struct rectangle_t {
  double width, height;
  point_t pos;
};

struct iShape {
  virtual ~iShape() = default;

  virtual double getArea() const = 0;
  virtual rectangle_t getFrameRect() const = 0;
  virtual void move(point_t new_center) = 0;
  virtual void move(double x, double y) = 0;
  virtual void scale(double k) = 0;
};

#endif
