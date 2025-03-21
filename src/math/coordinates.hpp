#ifndef SCREEN_TO_ISO_HPP
#define SCREEN_TO_ISO_HPP

#include <glm/glm.hpp>

namespace Math {
  glm::vec2 screenToIso(glm::vec2 screenPos, float tileWidth, float tileHeight);
  glm::vec2 isoToScreen(glm::vec2 isoPos);
};

#endif