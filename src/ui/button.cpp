#include <ui/button.hpp>

namespace Ui {
  Button::Button(const SkRect& bounds, const char* text) : Base(bounds), m_label(text) {
    setupFont();
  }

  Button::Button(const int& padding, const char* text) : Base(SkRect::MakeEmpty()), m_label(text) {
    setupFont();
    setupBounds();
  }

  void Button::setupFont() {
    sk_sp<SkFontMgr> mgr = SkFontMgr_New_FontConfig(nullptr, SkFontScanner_Make_FreeType());
    sk_sp<SkTypeface> typeface = mgr->matchFamilyStyle("Inter", SkFontStyle());
    if (!typeface) {
      std::cerr << "Failed to load font." << std::endl;
      return;
    }

    m_font = SkFont(typeface, m_fontSize);
    m_font.setEdging(SkFont::Edging::kAntiAlias);
  }

  void Button::update() {
    
  }

  void Button::draw(SkCanvas* canvas) {
    SkColor bgColor;
    if (!m_isEnabled) {
      bgColor = m_disabledColor;
    } else if (m_isPressed) {
      bgColor = m_pressedColor;
    } else if (m_isHovered) {
      bgColor = m_hoverColor;
    } else {
      bgColor = m_normalColor;
    }

    SkPaint paint;
    paint.setColor(bgColor);
    paint.setAntiAlias(true);
    paint.setStyle(SkPaint::kFill_Style);

    /* Draw button's background */
    SkRRect rect = SkRRect::MakeRectXY(m_bounds, m_cornerRadius, m_cornerRadius);
    canvas->drawRRect(rect, paint);

    /* Draw button's border */
    paint.setColor(SkColorSetRGB(255, 255, 255));
    paint.setStyle(SkPaint::kStroke_Style);
    paint.setStrokeWidth(1.0f);
    canvas->drawRRect(rect, paint);

    /* Draw button's label */
    paint.setColor(m_isEnabled ? m_textColor : m_textDisabledColor);
    paint.setAntiAlias(true);
    
    /* Draw centered */
    SkScalar width = m_font.measureText(m_label.c_str(), m_label.size(), SkTextEncoding::kUTF8);
    SkScalar height = m_font.getSize();
    SkScalar x = m_bounds.centerX() - width / 2;
    SkScalar y = m_bounds.centerY() + (height / 2) - 3;
    canvas->drawSimpleText(m_label.c_str(), m_label.size(), SkTextEncoding::kUTF8, x, y, m_font, paint);
  }

  void Button::updateBounds(const SkRect& bounds) {
    m_bounds = bounds;
  }

  void Button::onMouseClick() {
    if (m_isEnabled && m_onClickCb) {
      m_onClickCb();
    }
  }

  void Button::onMouseMove(float x, float y) {
    if (m_bounds.contains(x, y)) {
      onMouseEnter();
    } else {
      onMouseLeave();
    }
  }

  void Button::onMouseEnter() {
    m_isHovered = true;
  }

  void Button::onMouseLeave() {
    m_isHovered = false;
  }

  void Button::onMouseButton(float x, float y, bool pressed) {
    if (m_bounds.contains(x, y)) {
      m_isPressed = pressed;
      if (!pressed) {
        onMouseClick();
      }
    }
  }

  void Button::setColors(SkColor normal, SkColor hover, SkColor pressed, SkColor disabled) {
    m_normalColor = normal;
    m_hoverColor = hover;
    m_pressedColor = pressed;
    m_disabledColor = disabled;
  }

  void Button::setCornerRadius(float radius) {
    m_cornerRadius = radius;
  }

  void Button::onClick(std::function<void()> cb) {
    m_onClickCb = cb;
  }

  void Button::setFontSize(float size) {
    m_fontSize = size;
    m_font.setSize(size);
    setupBounds();
  }

  void Button::setupBounds() {
    SkScalar width = m_font.measureText(m_label.c_str(), m_label.size(), SkTextEncoding::kUTF8);
    SkScalar height = m_font.getSize();
    m_bounds = SkRect::MakeXYWH(m_bounds.x(), m_bounds.y(), width + 10, height + 10);
  }
};