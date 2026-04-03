#include "Rectangle.hpp"

Rectangle::Rectangle(point_t p, double a, double b):
Shape(),
width(a),
length(b)
{
  pos = p;
}

double Rectangle::getArea()
{
  return width * length;
}

rectangle_t Rectangle::getFrameRect()
{
  return rectangle_t(pos, width, length);
}

rectangle_t Rectangle::frame(Rectangle * r)
{
  return rectangle_t(r->pos, r->width, r->length);
}

void Rectangle::move(point_t p)
{
  pos = p;
}

void Rectangle::scale(double k)
{
  width *= k;
  length *= k;
}
