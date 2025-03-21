#include <ui/toolbar.hpp>

Toolbar::Toolbar(glm::vec3 position, float buttonSize, float spacing)
  : m_position(position), m_buttonSize(buttonSize), m_spacing(spacing), m_currentTool(nullptr) {}

void Toolbar::addTool(const std::string& name, std::function<std::unique_ptr<Tool>()> callback) {
  auto button = std::make_unique<Ui::Button>(m_buttonSize, name.c_str());
  button->setColors(SK_ColorGRAY, SK_ColorLTGRAY, SK_ColorGRAY, SK_ColorGRAY);
  button->onClick([this, &callback]() {
    m_currentTool = callback().get();
  });

  m_buttons.push_back({std::move(button), callback});
}

void Toolbar::draw(SkCanvas* canvas) {
  SkPaint paint;
  paint.setColor(SK_ColorGRAY);
  paint.setStyle(SkPaint::kFill_Style);

  SkRect rect = SkRect::MakeXYWH(m_position.x, m_position.y, m_buttonSize, m_buttonSize);
  canvas->drawRect(rect, paint);

  for (int i = 0; i < m_buttons.size(); i++) {
    SkPoint point = {m_position.x, m_position.y + (m_buttonSize + m_spacing) * i};
    // m_buttons[i].button->setPosition(glm::vec3(m_position.x, m_position.y + (m_buttonSize + m_spacing) * i, 0.0f));
    m_buttons[i].button->draw(canvas);
  }
}

void Toolbar::handleClick(glm::vec2 clickPosition) {
  for (int i = 0; i < m_buttons.size(); i++) {
    SkPoint point = {m_position.x, m_position.y + (m_buttonSize + m_spacing) * i};
    if (m_buttons[i].button->isInside(point)) {
      m_buttons[i].button->click();
    }
  }
}

Tool* Toolbar::getCurrentTool() const {
  return m_currentTool;
}

