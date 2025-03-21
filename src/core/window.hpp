#ifndef WINDOW_HPP
#define WINDOW_HPP
#include <GLFW/glfw3.h>
#include <stdexcept>

class Window {
  public:
    Window(int width, int height, const char* title);
    ~Window();

    bool shouldClose() const;
    void pollEvents();
    void swapBuffers();

    GLFWwindow* getHandle() const;
    void getSize(int& width, int& height) const;

  private:
    GLFWwindow* m_handle;
};

#endif