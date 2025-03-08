#ifndef LAYOUT_HPP
#define LAYOUT_HPP
#include <ui/base.hpp>

namespace Ui {
  class Layout : public Base {
    protected:
      std::vector<std::shared_ptr<Base>> m_childrens;
      float m_padding;
      bool m_needsLayout = true;

    public:
      Layout(const SkRect& bounds, float padding = 0.0f);
      virtual ~Layout() = default;

      virtual void addChild(std::shared_ptr<Base> child);

      template<typename T, typename... Args>
      std::shared_ptr<T> createChild(Args&&... args) {
        auto element = std::make_shared<T>(std::forward<Args>(args)...);
        addChild(element);
        return element;
      }

      void removeChild(const std::shared_ptr<Base>& child);
      void clearChildren();
      size_t childrenCount() const;
      void setPadding(float padding);

      /* Overrides */
      void update() override;
      void draw(SkCanvas* canvas) override;
      void onMouseMove(float x, float y) override;
      void onMouseButton(float x, float y, bool down) override;
      void onMouseEnter() override {}
      void onMouseLeave() override {}
      void onKeyDown(int key) override;
      void onKeyUp(int key) override;

    protected:
      virtual void layout() = 0;
  };
};

#endif