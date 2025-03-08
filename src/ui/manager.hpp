#ifndef MANAGER_HPP
#define MANAGER_HPP
#include <ui/base.hpp>

namespace Ui {
  class Manager {
    public:
      Manager() = default;

      void draw(SkCanvas* canvas);
      void update();
      void handleMouseMove(float x, float y);
      void handleMouseButton(float x, float y, bool pressed);

      template <typename T, typename... Args>
      T* addElement(Args&&... args) {
        m_elements.push_back(std::make_unique<T>(std::forward<Args>(args)...));
        return static_cast<T*>(m_elements.back().get());
      }

    private:
      std::vector<std::unique_ptr<Base>> m_elements;
  };
}

#endif