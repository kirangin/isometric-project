#include <ui/manager.hpp>

namespace Ui {
  void Manager::draw(SkCanvas* canvas) {
    if (m_rootLayout) {
      m_rootLayout->draw(canvas);
    }

    for (auto& element : m_elements) {
      if (element->isEnabled()) {
        element->draw(canvas);
      }
    }
  }

  void Manager::update() {
    if (m_rootLayout) {
      m_rootLayout->update();
    }

    for (auto& element : m_elements) {
      if (element->isEnabled()) {
        element->update();
      }
    }
  }

  void Manager::handleMouseMove(float x, float y) {
    if (m_rootLayout) {
      m_rootLayout->onMouseMove(x, y);
    }
    
    for (auto& element : m_elements) {
      if (element->isEnabled()) {
        element->onMouseMove(x, y);
      }
    }
  }

  void Manager::handleMouseButton(float x, float y, bool pressed) {
    if (m_rootLayout) {
      m_rootLayout->onMouseButton(x, y, pressed);
    }

    for (auto& element : m_elements) {
      if (element->isEnabled()) {
        if (element->contains(x, y)) {
          element->onMouseButton(x, y, pressed);
        }
      }
    }
  }

  void Manager::setLayout(std::shared_ptr<Layout> layout) {
    m_rootLayout = layout;
    m_elements.clear();
  }

  std::shared_ptr<Layout> Manager::getLayout() const {
    return m_rootLayout;
  }
}