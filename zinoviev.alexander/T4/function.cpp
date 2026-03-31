#include "function.hpp"

zinoviev::rectangle_t zinoviev::getAllFrameRect(const std::vector< std::weak_ptr< Shape > >& shapes)
{
  if (shapes.empty())
	  return rectangle_t{};

  double x_min = std::numeric_limits<double>::max();
	double y_min = std::numeric_limits<double>::max();
	double x_max = std::numeric_limits<double>::lowest();
	double y_max = std::numeric_limits<double>::lowest();

	bool found = false;
	for (size_t i = 0; i < shapes.size(); ++i)
  {
		auto shape = shapes[i].lock();

		if (shape)
    {
			found = true;

      rectangle_t frame = shape->getFrameRect();

      double half_W = 0.5 * frame.width;
      double half_H = 0.5 * frame.height;

      double left = frame.pos.x - half_W;
      double right = frame.pos.x + half_W;
      double bottom = frame.pos.y - half_H;
      double top = frame.pos.y + half_H;

      if (left < x_min)
      	x_min = left;

			if (right > x_max)
      	x_max = right;

      if (bottom < y_min)
      	y_min = bottom;

			if (top > y_max)
      	y_max = top;
    }
	}

	if (!found)
    return rectangle_t{};

	double width = x_max - x_min;
	double height = y_max - y_min;
	point_t center = { 0.5 * (x_max + x_min), 0.5 * (y_max + y_min) };

	return rectangle_t(center, width, height);
}
