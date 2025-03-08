#include <ui/input.hpp>

namespace Ui {
  Input::Input(const SkRect& bounds, const char* placeholder, std::string& text) : Base(bounds), m_placeholder(placeholder), m_text(text) {
    m_backgroundColor = SkColorSetRGB(240, 240, 240);
    m_borderColor = SkColorSetRGB(200, 200, 200);
    m_font.setSize(16.0f);
    m_font.setEdging(SkFont::Edging::kSubpixelAntiAlias);
    m_cursorPos = m_text.size() + 1;
    setupFont();
  }

  void Input::setPadding(float padding) {
    m_padding = padding;
  }

  std::string& Input::text() {
    return m_text;
  }

  void Input::setText(const std::string& text) {
    m_text = text;
  }

  void Input::setFocus(bool focus) {
    m_focus = focus;
  }

  void Input::setInputType(InputType type) {
    m_inputType = type;
  }

  void Input::update() {}

  void Input::draw(SkCanvas* canvas) {
    if (!m_isVisible) return;

    /* Draw background */
    SkRRect rrect;
    rrect.setNinePatch(m_bounds, m_padding, m_padding, m_padding, m_padding);
    
    SkPaint paint;
    paint.setColor(m_backgroundColor);
    paint.setAntiAlias(true);
    paint.setStyle(SkPaint::kFill_Style);
    canvas->drawRRect(rrect, paint);

    /* Draw border */
    paint.setColor(m_borderColor);
    paint.setStyle(SkPaint::kStroke_Style);
    paint.setStrokeWidth(1.0f);
    canvas->drawRRect(rrect, paint);

    /* Draw text */
    paint.setColor(SkColorSetRGB(10, 10, 10));

    SkRect textBounds = m_bounds;
    textBounds.inset(m_padding, m_padding);
    canvas->drawSimpleText(m_text.c_str(), m_text.size(), SkTextEncoding::kUTF8, textBounds.left(), textBounds.top() + m_font.getSize(), m_font, paint);

    /* Draw cursor */
    if (m_focus) {
      SkScalar cursorX = m_font.measureText(m_text.c_str(), m_cursorPos, SkTextEncoding::kUTF8);
      SkScalar cursorY = m_bounds.top() + m_padding;
      SkScalar cursorHeight = m_font.getSize();
      SkRect cursorBounds = SkRect::MakeXYWH(cursorX, cursorY, 1.0f, cursorHeight);
      canvas->drawRect(cursorBounds, paint);
    }
  }

  void Input::setupFont() {
    sk_sp<SkFontMgr> mgr = SkFontMgr_New_FontConfig(nullptr, SkFontScanner_Make_FreeType());
    sk_sp<SkTypeface> typeface = mgr->legacyMakeTypeface(DEFAULT_FONT_NAME, SkFontStyle());
    if (!typeface) {
      std::cerr << "Failed to load font." << std::endl;
      return;
    }

    m_font = SkFont(typeface, m_fontSize);
    m_font.setEdging(SkFont::Edging::kSubpixelAntiAlias);
  }

  void Input::updateBounds(const SkRect& bounds) {
    m_bounds = bounds;
  }

  void Input::onMouseMove(float x, float y) {
    if (m_bounds.contains(x, y)) {
      onMouseEnter();
    } else {
      onMouseLeave();
    }
  }

  void Input::onMouseButton(float x, float y, bool down) {
    
  }

  void Input::onMouseEnter() {
    m_isHovered = true;
  }

  void Input::onMouseLeave() {
    m_isHovered = false;
  }

  void Input::onKeyDown(int key) {
    std::cout << "Key: " << key << std::endl;
    if (!m_focus) return;

    // If backspace key is pressed
    if (key == 259 && m_cursorPos > 0) {
      m_text.erase(m_cursorPos - 1, 1);
      m_cursorPos--;
    } else {
      m_text.insert(m_cursorPos - 1, 1, key);
      m_cursorPos++;
    }
  }

  void Input::onKeyUp(int key) {
    std::cout << "Key: " << key << std::endl;
  }
};