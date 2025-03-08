#ifndef VBOX_LAYOUT_HPP
#define VBOX_LAYOUT_HPP
#include <ui/layout.hpp>

namespace Ui {
  class VBoxLayout : public Layout {
    public:
      VBoxLayout(const SkRect& bounds, float gap = 0.0f);
      
      void setGap(float gap);
      float getGap() const;

    private:
      float m_gap = 0.0f;

    protected:
      void layout() override;
  };
};

#endif