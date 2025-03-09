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
      // Calculate text width up to cursor position
      SkScalar textWidth = m_font.measureText(m_text.c_str(), m_cursorPos, SkTextEncoding::kUTF8);
      
      // Draw cursor at correct position
      SkRect cursor = SkRect::MakeXYWH(
        m_bounds.left() + m_padding + textWidth,
        m_bounds.top() + m_padding + 1.0f,
        2.0f, 
        m_font.getSize()
      );
      canvas->drawRect(cursor, paint);
    }
  }

  void Input::setupFont() {
    sk_sp<SkFontMgr> mgr = SkFontMgr_New_FontConfig(nullptr, SkFontScanner_Make_FreeType());
    sk_sp<SkTypeface> typeface = mgr->matchFamilyStyle("Inter", SkFontStyle());
    if (!typeface) {
      std::cerr << "Failed to load font." << std::endl;
      return;
    }

    m_font = SkFont(typeface, m_fontSize);
    m_font.setEdging(SkFont::Edging::kAntiAlias);
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
    if (m_bounds.contains(x, y)) {
      setFocus(true);
    } else {
      setFocus(false);
    }
  }

  void Input::onMouseEnter() {
    m_isHovered = true;
  }

  void Input::onMouseLeave() {
    m_isHovered = false;
  }

  void Input::onKeyDown(int key, int mods) {
    if (!m_focus) return;

    /* Special keys */
    if (key == GLFW_KEY_BACKSPACE || key == GLFW_KEY_DELETE || key == GLFW_KEY_LEFT 
     || key == GLFW_KEY_RIGHT || key == GLFW_KEY_HOME || key == GLFW_KEY_END) {
      handleSpecialKeys(key);
      return;
    }

    /* Handle CTRL combination */
    if (mods & GLFW_MOD_CONTROL) {
      // TODO: Handle
    }
  }

  void Input::onChar(unsigned int key) {
    if (!m_focus && !isValidCharacter(key)) return;

    m_text.insert(m_cursorPos - 1, 1, key);
    m_cursorPos++;
  }

  void Input::handleSpecialKeys(int key) {
    switch (key) {
      case GLFW_KEY_BACKSPACE:
        if (m_cursorPos > 0) {
          m_text.erase(m_cursorPos - 1, 1);
          m_cursorPos--;
        }
        break;
      case GLFW_KEY_DELETE:
        if (m_cursorPos < m_text.length()) {
          m_text.erase(m_cursorPos, 1);
        }
        break;
      case GLFW_KEY_LEFT:
        if (m_cursorPos > 0) {
          m_cursorPos--;
        }
        break;
      case GLFW_KEY_RIGHT:
        if (m_cursorPos < m_text.length()) {
          m_cursorPos++;
        }
        break;
      case GLFW_KEY_HOME:
        m_cursorPos = 0;
        break;
      case GLFW_KEY_END:
        m_cursorPos = m_text.length();
        break;
    }
  }

  bool Input::isValidCharacter(unsigned int key) const {
    if (m_inputType == InputType::Numeric) {
      return (key >= '0' && key <= '9') ||
      key == '.' || key == '-';
    }

    return true;
  }
};