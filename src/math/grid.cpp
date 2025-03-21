#include <math/grid.hpp>
#include <math/coordinates.hpp>

namespace Math {
  glm::vec2 Grid::gridToScreen(glm::ivec2 gridPosition) const {
    return glm::vec2(gridPosition.x * tileWidth, gridPosition.y * tileHeight);
  }

  glm::ivec2 Grid::screenToGrid(glm::vec2 screenPosition) const {
    return glm::ivec2(screenPosition.x / tileWidth, screenPosition.y / tileHeight);
  }
};