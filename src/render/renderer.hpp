#ifndef RENDERER_HPP
#define RENDERER_HPP
#include <math/coordinates.hpp>
#include <core/SkCanvas.h>
#include <math/grid.hpp>
#include <core/SkPath.h>
#include <iostream>
using namespace Math;

class Renderer {
  public:
    static void drawGrid(SkCanvas* canvas, const Grid& grid);
    static void drawCommitedTiles(SkCanvas* canvas, const Grid& grid, const std::vector<glm::ivec2>& tiles);
    static void drawPreviewTiles(SkCanvas* canvas, const Grid& grid, const std::vector<glm::ivec2>& previewTiles);

  private:
    static void drawTile(SkCanvas* canvas, glm::vec2 screenPosition, const SkColor& color);
    static SkPath createCubePath(glm::vec2 center, float tileWidth, float tileHeight);

    inline static const SkColor GRID_COLOR = SkColorSetRGB(80, 80, 80);
    inline static const SkColor PREVIEW_COLOR = SkColorSetARGB(255, 0, 255, 0);
    inline static const SkColor COMMITED_COLOR = SkColorSetARGB(255, 0, 255, 0);
};

#endif