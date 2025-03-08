#ifndef MANAGER_HPP
#define MANAGER_HPP
#include <ui/base.hpp>
#include <ui/layout.hpp>

/* TODO: find better solution */
#include <ui/input.hpp>

namespace Ui {
  class Manager {
    public:
      Manager() = default;

      void draw(SkCanvas* canvas);
      void update();
      void handleMouseMove(float x, float y);
      void handleMouseButton(float x, float y, bool pressed);
      void handleKeyUp(int key);
      void handleKeyDown(int key);
      void setFocusedInput(std::shared_ptr<Input> input);

      void setLayout(std::shared_ptr<Layout> layout);
      std::shared_ptr<Layout> getLayout() const;

      template <typename T, typename... Args>
      T* addElement(Args&&... args) {
        m_elements.push_back(std::make_unique<T>(std::forward<Args>(args)...));
        return static_cast<T*>(m_elements.back().get());
      }

    private:
      std::shared_ptr<Layout> m_rootLayout;
      std::shared_ptr<Input> m_focusedInput;
  };
}

#endif