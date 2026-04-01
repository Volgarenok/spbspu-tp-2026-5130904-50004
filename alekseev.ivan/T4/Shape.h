#ifndef SHAPE_H
#define SHAPE_H

#include <cstddef>

namespace alekseev {
  const double PI = 3.14159265358979323846;

  struct point_t {
    double x_, y_;
  };

  struct rectangle_t {
    double width_, height_;
    point_t pos_;
  };

  struct iShape {
    virtual ~iShape() = default;

    virtual double getArea() const = 0;
    virtual rectangle_t getFrameRect() const = 0;
    virtual void move(point_t new_center) = 0;
    virtual void move(double x, double y) = 0;
    virtual void scale(double k) = 0;
  };

  struct Rectangle: iShape {
    Rectangle(double width, double height, point_t pos);

    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void move(point_t new_center) override;
    void move(double x, double y) override;
    void scale(double k) override;

    private:
      rectangle_t rect_;
  };

  struct Circle: iShape {
    Circle(double radius, point_t center);

    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void move(point_t new_center) override;
    void move(double x, double y) override;
    void scale(double k) override;

    private:
      double radius_;
      point_t center_;
  };

  struct Polygon: iShape {
    Polygon(point_t * points, size_t count);
    ~Polygon() override;

    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void move(point_t new_center) override;
    void move(double x, double y) override;
    void scale(double k) override;

    private:
      point_t * points_;
      size_t count_;
      point_t center_;
  };
}

#endif
