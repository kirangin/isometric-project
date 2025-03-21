#include <render/cube.hpp>

void drawCube(SkCanvas* canvas, glm::vec2 isoPos, float tileWidth, float tileHeight) {
  SkPath path;
  glm::vec2 screenPos = Math::isoToScreen(isoPos);
  
  // Diamond shape
  path.moveTo(screenPos.x, screenPos.y + tileHeight/2);
  path.lineTo(screenPos.x + tileWidth/2, screenPos.y);
  path.lineTo(screenPos.x, screenPos.y - tileHeight/2);
  path.lineTo(screenPos.x - tileWidth/2, screenPos.y);
  path.close();

  SkPaint paint;
  paint.setColor(SkColorSetRGB(0, 120, 215)); // Blue color
  canvas->drawPath(path, paint);
}

void drawCubeHighlight(SkCanvas* canvas, glm::vec2 isoPos, float tileWidth, float tileHeight) {
  glm::vec2 screenPos = Math::isoToScreen(isoPos);
  
  SkPaint paint;
  paint.setColor(SkColorSetRGB(255, 200, 0)); // Yellow highlight
  paint.setStyle(SkPaint::kStroke_Style);
  paint.setStrokeWidth(2.0f);

  // Highlight diamond shape
  canvas->drawLine(
    screenPos.x, screenPos.y + tileHeight/2,
    screenPos.x + tileWidth/2, screenPos.y,
    paint
  );

  canvas->drawLine(
    screenPos.x + tileWidth/2, screenPos.y,
    screenPos.x, screenPos.y - tileHeight/2,
    paint
  );

  canvas->drawLine(
    screenPos.x, screenPos.y - tileHeight/2,
    screenPos.x - tileWidth/2, screenPos.y,
    paint
  );

  canvas->drawLine(
    screenPos.x - tileWidth/2, screenPos.y,
    screenPos.x, screenPos.y + tileHeight/2,
    paint
  );
}
