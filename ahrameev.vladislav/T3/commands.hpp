#ifndef AHRAMEEV_COMMANDS_HPP
#define AHRAMEEV_COMMANDS_HPP

#include "polygon.hpp"
#include "bounding_box.hpp"

#include <sstream>
#include <vector>

namespace ahrameev
{

  void handlePermsCommand(
    const std::vector< Polygon >& polygons,
    std::istringstream& cmdStream);

  void handleInFrameCommand(
    const BoundingBox& globalBox,
    std::istringstream& cmdStream);

}

#endif