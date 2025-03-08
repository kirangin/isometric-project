#ifndef INPUT_HPP
#define INPUT_HPP
#include <ui/base.hpp>

#include <ports/SkFontMgr_fontconfig.h>
#include <ports/SkFontScanner_FreeType.h>

#include <core/SkString.h>
#include <core/SkTextBlob.h>

#define DEFAULT_FONT_NAME "./assets/Helvetica.ttf"

namespace Ui {
  enum InputType {
    FreeText,
    Numeric,
  };

  class Input : public Base {
    public:
      Input(const SkRect& bounds, const char* placeholder, std::string& text);
      
      void setPadding(float padding);
      std::string& text();
      void setText(const std::string& text);
      void setFocus(bool focus);
      void setInputType(InputType type);

      /* Overrides */
      void update() override;
      void draw(SkCanvas* canvas) override;
      void updateBounds(const SkRect& bounds) override;
      void onMouseMove(float x, float y) override;
      void onMouseButton(float x, float y, bool down) override;
      void onMouseEnter() override;
      void onMouseLeave() override;
      void onKeyDown(int key) override;
      void onKeyUp(int key) override;

    private:
      std::string m_placeholder;
      std::string m_text;

      bool m_focus = false;
      size_t m_cursorPos;
      float m_padding = 4.0f;
      InputType m_inputType = InputType::FreeText;

      SkColor m_backgroundColor;
      SkColor m_borderColor;
      SkFont m_font;
      float m_fontSize = 12.0f;

      void setupFont();
  };
}

#endif 