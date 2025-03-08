#include <iostream>
#define SK_GANESH
#define SK_GL
#include <GLFW/glfw3.h>
#include <core/SkCanvas.h>
#include <core/SkSurface.h>
#include <core/SkColorSpace.h>
#include <gpu/ganesh/GrDirectContext.h>
#include <gpu/ganesh/SkSurfaceGanesh.h>
#include <gpu/ganesh/GrBackendSurface.h>
#include <gpu/ganesh/gl/glx/GrGLMakeGLXInterface.h>
#include <gpu/ganesh/gl/GrGLBackendSurface.h>
#include <gpu/ganesh/gl/GrGLInterface.h>
#include <gpu/ganesh/gl/GrGLDirectContext.h>
#include <gpu/ganesh/gl/GrGLAssembleInterface.h>
#include <gpu/ganesh/SkSurfaceGanesh.h>

#include <ui/manager.hpp>
#include <ui/button.hpp>

// #define GL_FRAMEBUFFER_SRGB 0x8DB9
// #define GL_SRGB8_ALPHA8 0x8C43

GrDirectContext* sContext = nullptr;
SkSurface* sSurface = nullptr;

void errorCallback(int error, const char* description) {
  std::cerr << "Error: " << description << std::endl;
}

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, GLFW_TRUE);
  }
}

void initSkia(int w, int h) {
  auto interface = GrGLMakeNativeInterface();
  if (interface == nullptr) {
    std::cerr << "Failed to create native interface. Using backup plan..." << std::endl;
    
    interface = GrGLMakeAssembledInterface(nullptr, (GrGLGetProc)* [](void*, const char* p) -> void* {
      return (void*) glfwGetProcAddress(p);
    });

    if (interface == nullptr) {
      std::cerr << "Failed to create assembled interface." << std::endl;
      return;
    }
  }

  sContext = GrDirectContexts::MakeGL(interface).release();
  if (sContext == nullptr) {
    std::cerr << "Failed to create context." << std::endl;
    return;
  }

  GrGLFramebufferInfo framebufferInfo;
  framebufferInfo.fFBOID = 0;
  framebufferInfo.fFormat = GL_RGBA8;

  SkColorType colorType = kRGBA_8888_SkColorType;
  GrBackendRenderTarget backendRenderTarget = GrBackendRenderTargets::MakeGL(w, h, 0, 0, framebufferInfo);

  if (!sContext) {
    std::cerr << "Failed to create context." << std::endl;
    return;
  }

  if (backendRenderTarget.isValid() == false) {
    std::cerr << "Failed to create backend render target." << std::endl;
    return;
  }

  sSurface = SkSurfaces::WrapBackendRenderTarget(
    sContext, backendRenderTarget, kBottomLeft_GrSurfaceOrigin, colorType, nullptr, nullptr
  ).release();
  if (sSurface == nullptr) {
    std::cerr << "Failed to create surface." << std::endl;
    return;
  }
}

void cleanupSkia() {
  delete sSurface;
  delete sContext;
}

void setupUiCallback(GLFWwindow* window, Ui::Manager* uiManager) {
  glfwSetWindowUserPointer(window, uiManager);

  glfwSetCursorPosCallback(window, [](GLFWwindow* window, double x, double y) {
    Ui::Manager* uiManager = static_cast<Ui::Manager*>(glfwGetWindowUserPointer(window));
    uiManager->handleMouseMove(x, y);
  });

  glfwSetMouseButtonCallback(window, [](GLFWwindow* window, int button, int action, int mods) {
    Ui::Manager* uiManager = static_cast<Ui::Manager*>(glfwGetWindowUserPointer(window));
    double x, y;
    glfwGetCursorPos(window, &x, &y);
    uiManager->handleMouseButton(x, y, action == GLFW_PRESS);
  });
}

int main(int argc, const char* argv[]) {
  GLFWwindow* window;
  glfwSetErrorCallback(errorCallback);
  if (!glfwInit()) {
    std::cerr << "Failed to initialize GLFW." << std::endl;
    return -1;
  }

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  // glfwWindowHint(GLFW_SRGB_CAPABLE, GLFW_TRUE);
  glfwWindowHint(GLFW_STENCIL_BITS, 0);
  // glfwWindowHint(GLFW_ALPHA_BITS, 0);
  glfwWindowHint(GLFW_DEPTH_BITS, 0);

  window = glfwCreateWindow(800, 600, "Hello, Skia!", nullptr, nullptr);
  if (!window) {
    std::cerr << "Failed to create window." << std::endl;
    glfwTerminate();
    return -1;
  }

  glfwMakeContextCurrent(window);
  // glEnable(GL_FRAMEBUFFER_SRGB);

  initSkia(800, 600);

  glfwSwapInterval(1);
  glfwSetKeyCallback(window, keyCallback);

  SkCanvas* canvas = sSurface->getCanvas();

  Ui::Manager manager;
  Ui::Button* button = manager.addElement<Ui::Button>(12, "Click me!");
  // button->setColors(SK_ColorRED, SK_ColorGREEN, SK_ColorBLUE, SK_ColorGRAY);
  button->onClick([]() {
    std::cout << "Button clicked!" << std::endl;
  });
  button->setFontSize(12.0f);
  button->setCornerRadius(0.0f);

  setupUiCallback(window, &manager);

  while (!glfwWindowShouldClose(window)) {
    glfwPollEvents();
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0.0f, 1.0f, 0.0f, 1.0f);

    manager.draw(canvas);

    sContext->flush();
    glfwSwapBuffers(window);
  }

  cleanupSkia();
  glfwDestroyWindow(window);
  glfwTerminate();

  return 0;
}