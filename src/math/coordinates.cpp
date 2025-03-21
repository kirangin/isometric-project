#include <math/coordinates.hpp>

namespace Math {
  glm::vec2 screenToIso(glm::vec2 screenPos, float tileWidth, float tileHeight) {
    return glm::vec2(
      (screenPos.x / tileWidth) - (screenPos.y / tileHeight),
      (screenPos.x / tileWidth) + (screenPos.y / tileHeight)
    );
  }

  glm::vec2 isoToScreen(glm::vec2 isoPos) {
    return glm::vec2(
      (isoPos.x + isoPos.y) * 64 / 2,
      (isoPos.y - isoPos.x) * 32 / 2
    );
  }
};