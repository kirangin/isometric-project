#include <ui/manager.hpp>

namespace Ui {
  void Manager::draw(SkCanvas* canvas) {
    if (!m_rootLayout) return;
    m_rootLayout->draw(canvas);
  }

  void Manager::update() {
    if (!m_rootLayout) return;
    m_rootLayout->update();
  }

  void Manager::handleMouseMove(float x, float y) {
    if (!m_rootLayout) return;
    m_rootLayout->onMouseMove(x, y);
  }

  void Manager::handleMouseButton(float x, float y, bool pressed) {
    if (!m_rootLayout) return;
    m_rootLayout->onMouseButton(x, y, pressed);
  }

  void Manager::handleKeyUp(int key) {
    if (!m_rootLayout) return;
    m_rootLayout->onKeyUp(key);
  }

  void Manager::handleKeyDown(int key) {
    if (!m_rootLayout) return;
    m_rootLayout->onKeyDown(key);
  }

  void Manager::setFocusedInput(std::shared_ptr<Input> input) {
    if (m_focusedInput == nullptr) return;

    m_focusedInput = input;
    m_focusedInput->setFocus(true);
  }

  void Manager::setLayout(std::shared_ptr<Layout> layout) {
    m_rootLayout = layout;
  }

  std::shared_ptr<Layout> Manager::getLayout() const {
    return m_rootLayout;
  }
}