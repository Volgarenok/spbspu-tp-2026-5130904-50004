#include "Diamond.hpp"

Diamond::Diamond(point_t p, double a, double b):
vertDiag(a),
horDiag(b)
{
  pos = p;
}
double Diamond::getArea()
{
  return vertDiag * horDiag;
}

rectangle_t Diamond::getFrameRect()
{
  return rectangle_t{pos, horDiag, vertDiag};
}

void Diamond::move(point_t p)
{
  pos = p;
}

void Diamond::scale(double k)
{
  vertDiag *= k;
  horDiag *= k;
}

