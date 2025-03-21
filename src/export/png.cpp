#include <export/png.hpp>

namespace Export {
  void exportToPNG(SkSurface* surface, const char* filename, int width, int height, const std::vector<glm::vec2>& cubes, float tileWidth, float tileHeight) {
    // Save the current state of the surface
    SkCanvas* canvas = surface->getCanvas();
    canvas->save();
    
    // Clear any UI elements from the surface (temporary)
    canvas->clear(SK_ColorTRANSPARENT);
    
    // Redraw only the workspace content (grid and cubes)
    // drawIsometricGrid(canvas, tileWidth, tileHeight);
    for (const auto& cubePos : cubes) {
      drawCube(canvas, cubePos, tileWidth, tileHeight);
    }
    
    // Now export this clean surface
    SkBitmap bitmap;
    bitmap.allocN32Pixels(width, height);
    
    if (!surface->readPixels(bitmap.info(), bitmap.getPixels(), bitmap.rowBytes(), 0, 0)) {
      std::cerr << "Failed to read pixels from surface!" << std::endl;
      canvas->restore();
      return;
    }
    
    SkFILEWStream fileStream(filename);
    if (!fileStream.isValid()) {
      std::cerr << "Failed to open file stream for writing!" << std::endl;
      canvas->restore();
      return;
    }
    
    SkPngEncoder::Options options;
    if (!SkPngEncoder::Encode(&fileStream, bitmap.pixmap(), options)) {
      std::cerr << "Failed to encode PNG!" << std::endl;
      canvas->restore();
      return;
    }
    
    fileStream.flush();
    std::cout << "Exported to " << filename << std::endl;
    
    // Restore the canvas state (including UI elements)
    canvas->restore();
  }
};