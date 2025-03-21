#include <core/event_handler.hpp>

void EventHandler::registerCallbacks(GLFWwindow* window) {
  glfwSetMouseButtonCallback(window, mouseCallback);
  glfwSetKeyCallback(window, keyCallbackWrapper);
}