#ifndef SHAPE_H
#define SHAPE_H

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

    virtual double getArea() const;
    virtual rectangle_t getFrameRect() const;
    virtual void move(point_t new_center);
    virtual void move(double x, double y);
    virtual void scale(double k);

    private:
      rectangle_t rect_;
  };

  struct Circle: iShape {
    Circle(double radius, point_t center);

    virtual double getArea() const;
    virtual rectangle_t getFrameRect() const;
    virtual void move(point_t new_center);
    virtual void move(double x, double y);
    virtual void scale(double k);

    private:
      double radius_;
      point_t center_;
  };

  struct Polygon: iShape {
    Polygon(point_t * points);
    virtual ~Polygon();

    virtual double getArea() const;
    virtual rectangle_t getFrameRect() const;
    virtual void move(point_t new_center);
    virtual void move(double x, double y);
    virtual void scale(double k);

    private:
      point_t * points_;
      point_t center_;
  };
}

#endif
