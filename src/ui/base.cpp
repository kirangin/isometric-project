#include <ui/base.hpp>

namespace Ui {
  Base::Base(const SkRect& bounds) : m_bounds(bounds), m_isHovered(false), m_isPressed(false), m_isEnabled(true), m_isVisible(true) {}

  void Base::onMouseClick() {}

  void Base::update() {}

  void Base::updateBounds(const SkRect& bounds) {
    m_bounds = bounds;
  }

  void Base::onMouseMove(float x, float y) {
    if (m_bounds.contains(x, y)) {
      m_isHovered = true;
    } else {
      m_isHovered = false;
    }
  }

  bool Base::contains(float x, float y) const {
    return m_bounds.contains(x, y);
  }

  void Base::setEnabled(bool enabled) {
    m_isEnabled = enabled;
  }

  bool Base::isEnabled() const {
    return m_isEnabled;
  }

  SkRect Base::getBounds() const {
    return m_bounds;
  }

  void Base::onMouseButton(float x, float y, bool pressed) {
    if (m_bounds.contains(x, y)) {
      m_isPressed = pressed;
      if (!pressed) {
        onMouseClick();
      }
    }
  }

  void Base::onKeyUp(int key) {}
  void Base::onKeyDown(int key, int mods) {}

  void Base::getFlatList(std::vector<std::shared_ptr<Base>>& list) {
    list.push_back(std::shared_ptr<Base>(this));

    for (auto& child : m_children) {
      child->getFlatList(list);
    }
  }

  SkPoint Base::globalToLocal(float x, float y) const {
    SkPoint local = { x - m_bounds.left(), y - m_bounds.top() };
    if (m_parent) {
      return m_parent->globalToLocal(local.x(), local.y());
    }
    return local;
  }

  void Base::onChar(unsigned int key) {}
};