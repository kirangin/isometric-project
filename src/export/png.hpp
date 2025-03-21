#ifndef PNG_HPP
#define PNG_HPP
#include <iostream>
#include <vector>
#include <core/SkSurface.h>
#include <core/SkData.h>
#include <core/SkBitmap.h>
#include <codec/SkEncodedImageFormat.h>
#include <encode/SkPngEncoder.h>
#include <core/SkStream.h>
#include <core/SkCanvas.h>
#include <glm/glm.hpp>
#include <render/cube.hpp>

namespace Export {
  void exportToPNG(SkSurface* surface, const char* filename, int width, int height, const std::vector<glm::vec2>& cubes, float tileWidth, float tileHeight);
};

#endif