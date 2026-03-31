#ifndef RECTANGLE_T_HPP

#define RECTANGLE_T_HPP
#include "point_t.hpp"

namespace zinoviev
{
	struct rectangle_t
	{
		point_t pos;
		double width;
		double height;

		rectangle_t() :
			width(0.0),
			height(0.0)
		{
		}

		rectangle_t(point_t p, double w, double h) :
			pos(p),
			width(w),
			height(h)
		{
		}
	};
}
#endif 
