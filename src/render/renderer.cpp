#include <render/renderer.hpp>

void Renderer::drawGrid(SkCanvas* canvas, const Grid& grid) {
  SkPaint paint;
  paint.setColor(GRID_COLOR);
  paint.setStyle(SkPaint::kStroke_Style);
  paint.setStrokeWidth(1.0f);

  // Y-axis
  for (int x = -40; x <= 40; x++) {
    for (int y = -40; y <= 40; y++) {
      glm::vec2 screenPos = {
        (x - y) * grid.tileWidth  / 2,
        (x + y) * grid.tileHeight / 2
      };

      canvas->drawLine(
        screenPos.x, screenPos.y - grid.tileHeight,
        screenPos.x + grid.tileWidth, screenPos.y,
        paint
      );
    }
  }

  // X-axis
  for (int x = -40; x <= 40; x++) {
    for (int y = -40; y <= 40; y++) {
      glm::vec2 screenPos = {
        (x - y) * grid.tileWidth  / 2,
        (x + y) * grid.tileHeight / 2
      };

      canvas->drawLine(
        screenPos.x, screenPos.y + grid.tileHeight,
        screenPos.x + grid.tileWidth, screenPos.y,
        paint
      );
    }
  }
}

void Renderer::drawCommitedTiles(SkCanvas* canvas, const Grid& grid, const std::vector<glm::ivec2>& tiles) {
  for (const auto& tile : tiles) {
    glm::vec2 screenPos = grid.gridToScreen(tile);
    drawTile(canvas, screenPos, COMMITED_COLOR);
  }
}

void Renderer::drawPreviewTiles(SkCanvas* canvas, const Grid& grid, const std::vector<glm::ivec2>& previewTiles) {
  for (const auto& tile : previewTiles) {
    glm::vec2 screenPos = grid.gridToScreen(tile);
    drawTile(canvas, screenPos, PREVIEW_COLOR);
  }
}

void Renderer::drawTile(SkCanvas* canvas, glm::vec2 screenPosition, const SkColor& color) {
  SkPaint paint;
  paint.setColor(color);
  paint.setStyle(SkPaint::kFill_Style);
  paint.setAntiAlias(true);

  Grid grid;
  SkPath path = createCubePath(screenPosition, grid.tileWidth, grid.tileHeight);
  canvas->drawPath(path, paint);
}

SkPath Renderer::createCubePath(glm::vec2 center, float tileWidth, float tileHeight) {
  SkPath path;
  const float halfWidth = tileWidth;
  const float halfHeight = tileHeight;
  
  path.moveTo(center.x, center.y + halfHeight); // Bottom point
  path.lineTo(center.x + halfWidth, center.y);  // Right point
  path.lineTo(center.x, center.y - halfHeight); // Top point
  path.lineTo(center.x - halfWidth, center.y);  // Left point
  path.close();
  
  return path;
}
