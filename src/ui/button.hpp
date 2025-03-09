#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <ui/base.hpp>

#include <ports/SkFontMgr_fontconfig.h>
#include <ports/SkFontScanner_FreeType.h>

#include <core/SkString.h>

namespace Ui {
  class Button : public Base {
    public:
      Button(const SkRect& bounds, const char* text);
      Button(const int& padding, const char* text);
      
      void update() override;
      void draw(SkCanvas* canvas) override;
      void updateBounds(const SkRect& bounds) override;
      
      void onMouseClick() override;
      void onMouseEnter() override;
      void onMouseLeave() override;
      void onMouseMove(float x, float y) override;
      void onMouseButton(float x, float y, bool pressed) override;
      void setColors(SkColor normal, SkColor hover, SkColor pressed, SkColor disabled);
      void setCornerRadius(float radius);
      void setFontSize(float size);
      void onClick(std::function<void()> cb);
      
    private:
      std::string m_label;
      std::function<void()> m_onClickCb;
      SkColor m_normalColor = SK_ColorLTGRAY;
      SkColor m_hoverColor = SK_ColorGRAY;
      SkColor m_pressedColor = SkColorSetRGB(80, 80, 80);
      SkColor m_disabledColor = SkColorSetRGB(180, 180, 180);
      SkColor m_textColor = SK_ColorBLACK;
      SkColor m_textDisabledColor = SkColorSetRGB(120, 120, 120);
      float m_cornerRadius = 2.0f;
      float m_fontSize = 12.0f;

      SkFont m_font;
      void setupFont();
      void setupBounds();
  };
};

#endif