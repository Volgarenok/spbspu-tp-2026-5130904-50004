#ifndef FUNCTION_HPP

#define FUNCTION_HPP

#include "shape.hpp"
#include <vector>
#include <memory>
#include <limits>
#include <iostream>

namespace zinoviev
{
	rectangle_t getAllFrameRect(const std::vector< std::weak_ptr< Shape > >& shapes);
	void printFigure(const std::weak_ptr< Shape >& figure, const std::string& name, size_t id);
	void printAllFigures(const std::vector< std::weak_ptr< Shape > >& figures, const std::vector< std::string >& names);
	void printTotalFrame(const rectangle_t& frame);
	void scaleAllFigures(std::vector< std::weak_ptr< Shape > >& shapes, const point_t& point_scale, double k);
}
#endif
