#include <ui/manager.hpp>

namespace Ui {
  void Manager::draw(SkCanvas* canvas) {
    for (auto& element : m_elements) {
      if (element->isEnabled()) {
        element->draw(canvas);
      }
    }
  }

  void Manager::update() {
    for (auto& element : m_elements) {
      if (element->isEnabled()) {
        element->onMouseEnter();
      }
    }
  }

  void Manager::handleMouseMove(float x, float y) {
    for (auto& element : m_elements) {
      if (element->isEnabled()) {
        if (element->contains(x, y)) {
          element->onMouseEnter();
        } else {
          element->onMouseLeave();
        }
      }
    }
  }

  void Manager::handleMouseButton(float x, float y, bool pressed) {
    for (auto& element : m_elements) {
      if (element->isEnabled()) {
        if (element->contains(x, y)) {
          element->onMouseButton(x, y, pressed);
        }
      }
    }
  }
}