#ifndef OUTPUT_HPP
#define OUTPUT_HPP

#include "Shape.hpp"
#include <iostream>
#include <memory>
#include <vector>
namespace khairullin
{
  void output(std::vector< std::weak_ptr< khairullin::Shape > > & shapes);
}
#endif
