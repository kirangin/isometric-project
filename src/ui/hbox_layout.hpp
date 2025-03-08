#ifndef HBOX_LAYOUT_HPP
#define HBOX_LAYOUT_HPP
#include <ui/layout.hpp>

namespace Ui {
  class HBoxLayout : public Layout {
    public:
      HBoxLayout(const SkRect& bounds, float gap = 0.0f);
      
      void setGap(float gap);
      float getGap() const;

    private:
      float m_gap = 0.0f;

    protected:
      void layout() override;
  };
};

#endif