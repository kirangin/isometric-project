#include <iostream>
#define GLFW_EXPOSE_NATIVE_X11
#define GLFW_EXPOSE_NATIVE_GLX
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>
#include <core/SkCanvas.h>
#include <core/SkSurface.h>
#include <gpu/ganesh/gl/glx/GrGLMakeGLXInterface.h>
#include <gpu/ganesh/GrDirectContext.h>
#include <gpu/ganesh/SkSurfaceGanesh.h>
#include <gpu/ganesh/gl/GrGLBackendSurface.h>
#include <gpu/ganesh/gl/GrGLInterface.h>
#include <gpu/ganesh/gl/GrGLDirectContext.h>
#include <gpu/ganesh/SkSurfaceGanesh.h>
#include <X11/Xlib.h>

int main(int argc, char const *argv[]) {
  if (!glfwInit()) {
    std::cerr << "Failed to initialize GLFW" << std::endl;
    return -1;
  }

  GLFWwindow *window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
  if (!window) {
    std::cerr << "Failed to create window" << std::endl;
    glfwTerminate();
    return -1;
  }

  /* Skia */
  GrContextOptions opts;
  opts.fSuppressPrints = true;

  // Get the X11 Display, Window, and GLX Context
  Display* display = glfwGetX11Display();
  Window x11Window = glfwGetX11Window(window);
  GLXContext glxContext = glfwGetGLXContext(window);
  XVisualInfo* visualInfo;

  int chooseVisualAtt[] = {
    GLX_RGBA,
    GLX_DOUBLEBUFFER,
    GLX_STENCIL_SIZE, 8,
    None
  };
  visualInfo = glXChooseVisual(display, DefaultScreen(display), chooseVisualAtt);

  // Set GLX context with the current context
  glXCreateContext(display, visualInfo, glxContext, GL_TRUE);
  glXMakeContextCurrent(display, x11Window, x11Window, glxContext);

  sk_sp<const GrGLInterface> interface = GrGLInterfaces::MakeGLX();
  if (nullptr == glXGetCurrentContext()) {
    std::cerr << "Failed to create GLX context" << std::endl;
    return -1;
  }
  sk_sp<GrDirectContext> context = GrDirectContexts::MakeGL(interface, opts);

  int fbWidth, fbHeight;
  glfwGetFramebufferSize(window, &fbWidth, &fbHeight);

  GrGLFramebufferInfo info;
  info.fFBOID = 0;
  info.fFormat = GL_RGBA8;

  SkColorType colorType = kRGBA_8888_SkColorType;
  const SkImageInfo imageInfo = SkImageInfo::Make(fbWidth, fbHeight, colorType, kPremul_SkAlphaType);
  sk_sp<SkSurface> surface = SkSurfaces::RenderTarget(context.get(), skgpu::Budgeted::kYes, imageInfo);

  SkCanvas* canvas = surface->getCanvas();

  while (!glfwWindowShouldClose(window)) {
    canvas->clear(SK_ColorWHITE);

    SkPaint paint;
    paint.setColor(SK_ColorRED);
    paint.setAntiAlias(true);
    canvas->drawCircle(320, 240, 100, paint);

    context->flush();
    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glfwTerminate();
  glfwDestroyWindow(window);
  return 0;
}
