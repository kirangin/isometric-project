#include <ui/hbox_layout.hpp>

namespace Ui {
  HBoxLayout::HBoxLayout(const SkRect& bounds, float gap)
    : Layout(bounds, gap) {}

  void HBoxLayout::setGap(float gap) {
    m_gap = gap;
    m_needsLayout = true;
  }

  float HBoxLayout::getGap() const {
    return m_gap;
  }

  void HBoxLayout::layout() {
    if (m_childrens.empty()) return;

    float availWidth = m_bounds.width() - (2 * m_padding) - (m_gap * (m_childrens.size() - 1));
    float childWidth = availWidth / m_childrens.size();
    float currentX = m_bounds.left() + m_padding;
    float currentHeight = m_bounds.height() - (2 * m_padding);

    for (auto& children : m_childrens) {
      SkRect childBounds = SkRect::MakeXYWH(currentX, m_bounds.top() + m_padding, childWidth, currentHeight);

      Layout* layoutChild = dynamic_cast<Layout*>(children.get());
      if (layoutChild) {
        layoutChild->updateBounds(childBounds);
        layoutChild->update();
      } else {
        children->updateBounds(childBounds);
      }

      currentX += childWidth + m_gap;
    }
  }
};