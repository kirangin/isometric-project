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
#include <ui/vbox_layout.hpp>
#include <ui/hbox_layout.hpp>

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

  auto mainVertLayout = std::make_shared<Ui::VBoxLayout>(SkRect::MakeXYWH(0, 0, 800, 600), 4.0f);
  auto topLayout = std::make_shared<Ui::HBoxLayout>(SkRect::MakeEmpty(), 0.0f);

  mainVertLayout->setGap(4.0f);
  topLayout->setGap(4.0f);

  auto btn1 = std::make_shared<Ui::Button>(10, "Button 1");
  auto btn2 = std::make_shared<Ui::Button>(10, "Button 2");
  auto btn3 = std::make_shared<Ui::Button>(10, "Button 3");
  btn1->onClick([]() {
    std::cout << "Button 1 clicked." << std::endl;
  });
  btn2->onClick([]() {
    std::cout << "Button 2 clicked." << std::endl;
  });
  btn3->onClick([]() {
    std::cout << "Button 3 clicked." << std::endl;
  });

  topLayout->addChild(btn1);
  topLayout->addChild(btn2);
  topLayout->addChild(btn3);

  auto btn4 = std::make_shared<Ui::Button>(0, "Button 4");
  auto btn5 = std::make_shared<Ui::Button>(0, "Button 5");
  auto btn6 = std::make_shared<Ui::Button>(0, "Button 6");

  btn4->onClick([]() {
    std::cout << "Button 4 clicked." << std::endl;
  });
  btn5->onClick([]() {
    std::cout << "Button 5 clicked." << std::endl;
  });
  btn6->onClick([]() {
    std::cout << "Button 6 clicked." << std::endl;
  });

  mainVertLayout->addChild(topLayout);
  mainVertLayout->addChild(btn4);
  mainVertLayout->addChild(btn5);
  mainVertLayout->addChild(btn6);

  manager.setLayout(mainVertLayout);

  setupUiCallback(window, &manager);

  while (!glfwWindowShouldClose(window)) {
    glfwPollEvents();
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0.0f, 1.0f, 0.0f, 1.0f);

    manager.update();
    manager.draw(canvas);

    sContext->flush();
    glfwSwapBuffers(window);
  }

  cleanupSkia();
  glfwDestroyWindow(window);
  glfwTerminate();

  return 0;
}