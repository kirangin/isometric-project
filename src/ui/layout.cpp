#include <ui/layout.hpp>

namespace Ui {
  Layout::Layout(const SkRect& bounds, float padding)
    : Base(bounds), m_padding(padding) {}

  void Layout::addChild(std::shared_ptr<Base> child) {
    m_childrens.push_back(child);
    m_needsLayout = true;
  }

  void Layout::removeChild(const std::shared_ptr<Base>& child) {
    auto it = std::find(m_childrens.begin(), m_childrens.end(), child);
    if (it != m_childrens.end()) {
      m_childrens.erase(it);
      m_needsLayout = true;
    }
  }

  void Layout::clearChildren() {
    m_childrens.clear();
    m_needsLayout = true;
  }

  size_t Layout::childrenCount() const {
    return m_childrens.size();
  }

  void Layout::setPadding(float padding) {
    m_padding = padding;
    m_needsLayout = true;
  }

  void Layout::update() {
    if (m_needsLayout) {
      layout();
      m_needsLayout = false;
    }

    for (auto& child : m_childrens) {
      child->update();
    }
  }

  void Layout::draw(SkCanvas* canvas) {
    for (auto& child : m_childrens) {
      child->draw(canvas);
    }
  }

  void Layout::onMouseMove(float x, float y) {
    for (auto& child : m_childrens) {
      child->onMouseMove(x, y);
    }
  }

  void Layout::onMouseButton(float x, float y, bool down) {
    for (auto& child : m_childrens) {
      child->onMouseButton(x, y, down);
    }
  }
};