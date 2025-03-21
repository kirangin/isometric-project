#ifndef EVENT_HANDLER_HPP
#define EVENT_HANDLER_HPP
#include <functional>
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>

class EventHandler {
  public:
    using MouseCbFn = std::function<void(glm::dvec2 position, int button, int action)>;
    using KeyCbFn = std::function<void(int key, int action)>;

    static void registerCallbacks(GLFWwindow* window);

    static void setMouseCallback(MouseCbFn cb) {
      s_mouseCb = cb;
    }

    static void setKeyCallback(KeyCbFn cb) {
      s_keyCb = cb;
    }

  private:
    static inline MouseCbFn s_mouseCb = nullptr;
    static inline KeyCbFn s_keyCb = nullptr;

    static void mouseCallback(GLFWwindow* window, int button, int action, int mods) {
      double x, y;
      glfwGetCursorPos(window, &x, &y);
      s_mouseCb({x, y}, button, action);
    }

    static void keyCallbackWrapper(GLFWwindow* window, int key, int scancode, int action, int mods) {
      s_keyCb(key, action);
    }
};

#endif