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
      void handleKeyDown(int key, int mods);
      void handleChar(unsigned int key);

      void setLayout(std::shared_ptr<Layout> layout);
      std::shared_ptr<Layout> getLayout() const;

    private:
      std::shared_ptr<Layout> m_layout;

  };
}

#endif