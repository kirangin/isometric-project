#ifndef GRID_HPP
#define GRID_HPP
#include <glm/glm.hpp>

namespace Math {
  struct Grid {
    float tileWidth = 64.0f;
    float tileHeight = 32.0f;
    bool snapEnabled = true;

    glm::vec2 gridToScreen(glm::ivec2 gridPosition) const;
    glm::ivec2 screenToGrid(glm::vec2 screenPosition) const;
  };
};

#endif 