#include <ui/vbox_layout.hpp>

namespace Ui {
  VBoxLayout::VBoxLayout(const SkRect& bounds, float gap)
    : Layout(bounds, gap) {}

  void VBoxLayout::setGap(float gap) {
    m_gap = gap;
  }

  float VBoxLayout::getGap() const {
    return m_gap;
  }

  void VBoxLayout::layout() {
    if (m_childrens.empty()) return;

    float availHeight = m_bounds.height() - (2 * m_padding) - (m_gap * (m_childrens.size() - 1));
    float childHeight = availHeight / m_childrens.size();
    float currentY = m_bounds.top() + m_padding;
    float contentWidth = m_bounds.width() - (2 * m_padding);

    for (auto child : m_childrens) {
      SkRect childBounds = SkRect::MakeXYWH(m_bounds.left() + m_padding, currentY, contentWidth, childHeight);

      Layout* layout = dynamic_cast<Layout*>(child.get());
      if (layout) {
        layout->updateBounds(childBounds);
      } else {
        child->updateBounds(childBounds);
      }

      currentY += childHeight + m_gap;
    }
  }
}