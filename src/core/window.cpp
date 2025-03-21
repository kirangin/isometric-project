#include <core/window.hpp>

Window::Window(int width, int height, const char* title) {
  if (glfwInit() == GLFW_FALSE) {
    throw std::runtime_error("Failed to initialize GLFW.");
  }

  m_handle = glfwCreateWindow(width, height, title, nullptr, nullptr);
  if (m_handle == nullptr) {
    glfwTerminate();
    throw std::runtime_error("Failed to create window.");
  }

  glfwMakeContextCurrent(m_handle);
}

Window::~Window() {
  glfwDestroyWindow(m_handle);
  glfwTerminate();
}

bool Window::shouldClose() const {
  return glfwWindowShouldClose(m_handle);
}

void Window::pollEvents() {
  glfwPollEvents();
}

void Window::swapBuffers() {
  glfwSwapBuffers(m_handle);
}

GLFWwindow* Window::getHandle() const {
  return m_handle;
}

void Window::getSize(int& width, int& height) const {
  glfwGetWindowSize(m_handle, &width, &height);
}