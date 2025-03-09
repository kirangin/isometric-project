#include <ui/manager.hpp>

namespace Ui {
  void Manager::draw(SkCanvas* canvas) {
    if (!m_layout) return;
    m_layout->draw(canvas);
  }

  void Manager::update() {
    if (!m_layout) return;
    m_layout->update();
  }

  void Manager::handleMouseMove(float x, float y) {
    if (!m_layout) return;
    m_layout->onMouseMove(x, y);
  }

  void Manager::handleMouseButton(float x, float y, bool pressed) {
    if (!m_layout) return;
    m_layout->onMouseButton(x, y, pressed);
  }

  void Manager::handleKeyUp(int key) {
    if (!m_layout) return;
    m_layout->onKeyUp(key);
  }

  void Manager::handleKeyDown(int key, int mods) {
    if (!m_layout) return;
    m_layout->onKeyDown(key, mods);
  }

  void Manager::handleChar(unsigned int key) {
    if (!m_layout) return;
    m_layout->onChar(key);
  }

  void Manager::setLayout(std::shared_ptr<Layout> layout) {
    m_layout = layout;
  }

  std::shared_ptr<Layout> Manager::getLayout() const {
    return m_layout;
  }
}