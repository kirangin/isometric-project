#ifndef TOOLBAR_HPP
#define TOOLBAR_HPP
#include <ui/button.hpp>
#include <tools/tool.hpp>
#include <vector>
#include <memory>
#include <functional>

class Toolbar {
  public:
    Toolbar(glm::vec3 position, float buttonSize = 32.0f, float spacing = 4.0f);

    void addTool(const std::string& name, std::function<std::unique_ptr<Tool>()> callback);
    void draw(SkCanvas* canvas);
    void handleClick(glm::vec2 clickPosition);

    Tool* getCurrentTool() const;

  private:
    struct ToolButton {
      std::unique_ptr<Ui::Button> button;
      std::function<std::unique_ptr<Tool>()> callback;
    };

    glm::vec3 m_position;
    float m_buttonSize;
    float m_spacing;
    std::vector<ToolButton> m_buttons;
    Tool* m_currentTool;
};

#endif