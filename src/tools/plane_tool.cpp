#include <tools/plane_tool.hpp>

void PlaneTool::onDragStart(glm::ivec2 start) {
  m_start = start;
  m_previewTiles.clear();
}

void PlaneTool::onDrawUpdate(glm::ivec2 current) {
  m_previewTiles.clear();

  /* Calculate Rectangle Bounds */
  glm::ivec2 min = glm::min(m_start, current);
  glm::ivec2 max = glm::max(m_start, current);

  for (int x = min.x; x <= max.x; x++) {
    for (int y = min.y; y <= max.y; y++) {
      m_previewTiles.push_back({x, y});
    }
  }
}

void PlaneTool::onDragEnd() {
  
}