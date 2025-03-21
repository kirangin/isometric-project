#include <core/application.hpp>

Application::Application() {
  /* Create window instance */
  m_window = new Window(800, 600, "Skia Example");
  if (m_window == nullptr) {
    throw std::runtime_error("Failed to create window.");
  }

  /* Initialize event handling */
  EventHandler::registerCallbacks(m_window->getHandle());
  EventHandler::setMouseCallback([this](glm::dvec2 position, int button, int action) {
    handleMouse(position, button, action, 0);
  });
  EventHandler::setKeyCallback([this](int key, int action) {
    handleKey(key, action);
  });

  /* Initialize Skia */
  initSkia();
  initSurfaces();

  m_currentTool = std::make_unique<PlaneTool>();

  /* Initialize Layout */
  m_layout = std::make_shared<Ui::VBoxLayout>();
  m_uiManager.setLayout(m_layout);
}

Application::~Application() {
  delete m_window;
  delete m_context;
}

void Application::run() {
  while (!m_window->shouldClose()) {
    m_window->pollEvents();
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);

    /* Draw UI */
    {
      Renderer::drawGrid(m_canvas["UI"], m_grid);
      Renderer::drawCommitedTiles(m_canvas["UI"], m_grid, m_commitedTiles);

      if (m_isDrawing) {
        Renderer::drawPreviewTiles(m_canvas["UI"], m_grid, m_currentTool->getPreviewTiles());
      }
    }

    m_context->getContext()->flushAndSubmit();
    m_window->swapBuffers();
  }
}

void Application::initSkia() {
  auto interface = GrGLMakeNativeInterface();
  if (interface == nullptr) {
    // TODO: add logging
    interface = GrGLMakeAssembledInterface(nullptr, (GrGLGetProc)* [](void*, const char* p) -> void* {
      return (void*) glfwGetProcAddress(p);
    });

    if (interface == nullptr) {
      std::runtime_error("Failed to create assembled interface.");
      return;
    }
  }

  m_context = new RenderContext(interface);
  if (m_context == nullptr) {
    throw std::runtime_error("Failed to create context.");
    return;
  }
}

void Application::initSurfaces() {
  int width, height;
  m_window->getSize(width, height);

  auto colorType = kRGBA_8888_SkColorType;
  auto colorSpace = SkColorSpace::MakeSRGB();
  GrGLFramebufferInfo framebufferInfo;
  framebufferInfo.fFBOID = 0;
  framebufferInfo.fFormat = GL_RGBA8;

  /* UI Render Target */
  GrBackendRenderTarget uiBackendRenderTarget = GrBackendRenderTargets::MakeGL(width, height, 0, 0, framebufferInfo);
  if (uiBackendRenderTarget.isValid() == false) {
    throw std::runtime_error("Failed to create backend render target.");
    return;
  }

  m_uiSurface = SkSurfaces::WrapBackendRenderTarget(
    m_context->getContext().release(), uiBackendRenderTarget, kBottomLeft_GrSurfaceOrigin, colorType, nullptr, nullptr
  );
  if (m_uiSurface == nullptr) {
    throw std::runtime_error("Failed to create surface.");
    return;
  }

  /* Workspace Render Target */
  GrBackendRenderTarget workspaceBackendRenderTarget = GrBackendRenderTargets::MakeGL(width, height, 0, 0, framebufferInfo);
  m_workspaceSurface = SkSurfaces::WrapBackendRenderTarget(
    m_context->getContext().release(), workspaceBackendRenderTarget, kBottomLeft_GrSurfaceOrigin, colorType, nullptr, nullptr
  );
  if (m_workspaceSurface == nullptr) {
    throw std::runtime_error("Failed to create workspace surface.");
    return;
  }

  m_canvas["UI"] = m_uiSurface->getCanvas();
  m_canvas["WS"] = m_workspaceSurface->getCanvas();
}

void Application::handleMouse(glm::dvec2 position, int button, int action, int mods) {
  if (button == GLFW_MOUSE_BUTTON_LEFT) {
    glm::ivec2 gridPos = m_grid.screenToGrid(position);

    if (action == GLFW_PRESS) {
      if (!m_isDrawing) {
        m_dragStartPos = gridPos;
        m_currentTool->onDragStart(gridPos);
        m_isDrawing = true;
      } else if (action == GLFW_RELEASE && m_isDrawing) {
        const auto& preview = m_currentTool->getPreviewTiles();
        m_commitedTiles.insert(m_commitedTiles.end(), preview.begin(), preview.end());
        m_isDrawing = false;
      }
    }
  }

  /* Drag */
  if (m_isDrawing) {
    m_currentTool->onDrawUpdate(m_grid.screenToGrid(position));
  }
}

void Application::handleKey(int key, int action) {
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
    // m_window->close();
  }
}
