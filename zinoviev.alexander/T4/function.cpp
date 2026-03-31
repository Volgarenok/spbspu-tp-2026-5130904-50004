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
 function.cpp     double bottom = frame.pos.y - half_H;
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

void zinoviev::printFigure(const std::weak_ptr< Shape >& figure, const std::string& name, size_t id)
{
  auto shape = figure.lock();
  if (!shape)
  	throw std::runtime_error("Weak reference bad");

	rectangle_t frame = shape->getFrameRect();
  std::cout << id << "." << name << "\n";
  std::cout << "area = " << shape->getArea() << "\n";
  std::cout << "Frame: (" << frame.pos.x << "; " << frame.pos.y << "), width = " << frame.width \
  	<< ", height = " << frame.height << "\n";
}

void zinoviev::printAllFigures(const std::vector< std::weak_ptr< Shape > > & figures, const std::vector< std::string > & names)
{
	double total = 0.0;

	for (size_t i = 0; i < figures.size(); ++i)
  {
  	auto shape = figures[i].lock();
    if (shape)
    {
    	printFigure(figures[i], names[i], i + 1);
      total += shape->getArea();
    }
	}
  std::cout << "Total area = " << total << "\n";
}

void zinoviev::printTotalFrame(const rectangle_t& frame)
{
	std::cout << "Total framerect: center (" << frame.pos.x << "; " << frame.pos.y << ")" \
  	<< "width = " << frame.width << ", height = " << frame.height << "\n";
}

void zinoviev::scaleAllFigures(std::vector< std::weak_ptr< Shape > >& shapes, const point_t& point_scale, double k)
{
	for (size_t i = 0; i < shapes.size(); ++i)
  {
  	auto shape = shapes[i].lock();

		if (shape)
    {
    	rectangle_t old_frame = shape->getFrameRect();
      point_t point_on_frame = old_frame.pos;

      shape->move(point_scale);
      point_t new_point_frame = shape->getFrameRect().pos;

      double diff_x = point_on_frame.x - new_point_frame.x;
      double diff_y = point_on_frame.y - new_point_frame.y;

      shape->scale(k);

      shape->move(diff_x * k, diff_y * k);
		}
	}
}
