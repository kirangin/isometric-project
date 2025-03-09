#ifndef BASE_HPP
#define BASE_HPP

#include <core/SkCanvas.h>
#include <core/SkPaint.h>
#include <core/SkPath.h>
#include <core/SkRRect.h>
#include <core/SkTypeface.h>
#include <core/SkFont.h>
#include <core/SkFontMgr.h>
#include <core/SkData.h>  
#include <vector>
#include <string>
#include <functional>
#include <memory>
#include <iostream>

// Forward declaration for GLFW window
struct GLFWwindow;

namespace Ui {
  class Base {
    protected:
      SkRect m_bounds;
      bool m_isHovered;
      bool m_isPressed;
      bool m_isEnabled;
      bool m_isVisible;
      std::vector<std::shared_ptr<Base>> m_children;
      Base* m_parent = nullptr;

    public:
      Base(const SkRect& bounds);
      virtual ~Base() = default;

      virtual void update();
      virtual void updateBounds(const SkRect& bounds);
      virtual void draw(SkCanvas* canvas) = 0;
      virtual void onMouseEnter() = 0;
      virtual void onMouseLeave() = 0;

      virtual void onMouseMove(float x, float y);
      virtual void onMouseClick();
      virtual void onMouseButton(float x, float y, bool pressed);
      virtual void onKeyUp(int key);
      virtual void onKeyDown(int key, int mods);
      virtual void onChar(unsigned int key);

      virtual bool contains(float x, float y) const;
      virtual void getFlatList(std::vector<std::shared_ptr<Base>>& list);
      virtual SkPoint globalToLocal(float x, float y) const;

      void setEnabled(bool enabled);
      bool isEnabled() const;

      SkRect getBounds() const;
  };
};

#endif