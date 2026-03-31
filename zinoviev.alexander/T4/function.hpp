#ifndef FUNCTION_HPP

#define FUNCTION_HPP

#include "shape.hpp"
#include <vector>
#include <memory>

namespace zinoviev
{
	rectangle_t getAllFrameRect(const std::vector< std::weak_ptr< Shape > >& shapes);
}
#endif
