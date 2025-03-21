#ifndef APPLICATION_HPP
#define APPLICATION_HPP
#include <core/window.hpp>
#include <core/event_handler.hpp>
#include <core/render_context.hpp>
#include <tools/tool.hpp>
#include <tools/plane_tool.hpp>
#include <render/renderer.hpp>
#include <glm/glm.hpp>
#include <math/grid.hpp>
using namespace Math;

#define SK_GANESH
#define SK_GL
#include <GLFW/glfw3.h>
#include <core/SkCanvas.h>
#include <core/SkSurface.h>
#include <core/SkColorSpace.h>
#include <gpu/ganesh/SkSurfaceGanesh.h>
#include <gpu/ganesh/GrBackendSurface.h>
#include <gpu/ganesh/gl/glx/GrGLMakeGLXInterface.h>
#include <gpu/ganesh/gl/GrGLBackendSurface.h>
#include <gpu/ganesh/gl/GrGLInterface.h>
#include <gpu/ganesh/gl/GrGLAssembleInterface.h>
#include <gpu/ganesh/SkSurfaceGanesh.h>

#include <math/coordinates.hpp>
#include <render/cube.hpp>
#include <export/png.hpp>

#include <unordered_map>
#include <string>

#include <ui/manager.hpp>
#include <ui/manager.hpp>
#include <ui/vbox_layout.hpp>

class Application {
  public:
    Application();
    ~Application();
    void run();

  private:
    void initSkia();
    void initSurfaces();
    void handleMouse(glm::dvec2 position, int button, int action, int mods);
    void handleKey(int key, int action);

    Window* m_window = nullptr;
    RenderContext* m_context = nullptr;
    sk_sp<SkSurface> m_uiSurface = nullptr;
    sk_sp<SkSurface> m_workspaceSurface = nullptr;

    /* Application States */
    std::vector<glm::vec2> m_cubes;
    std::unordered_map<std::string, SkCanvas*> m_canvas;
    size_t m_selectedCubeIndex = -1;
    Ui::Manager m_uiManager;
    std::shared_ptr<Ui::Layout> m_layout;
    
    Grid m_grid;
    std::unique_ptr<Tool> m_currentTool;
    std::vector<glm::ivec2> m_commitedTiles;
    bool m_isDrawing = false;
    glm::ivec2 m_dragStartPos;
};

#endif