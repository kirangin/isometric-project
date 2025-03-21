#ifndef CUBE_HPP
#define CUBE_HPP
#include <math/coordinates.hpp>
#include <core/SkCanvas.h>
#include <core/SkPath.h>

void drawCube(SkCanvas* canvas, glm::vec2 isoPos, float tileWidth, float tileHeight);
void drawCubeHighlight(SkCanvas* canvas, glm::vec2 isoPos, float tileWidth, float tileHeight);

#endif