#ifndef PLANE_TOOL_HPP
#define PLANE_TOOL_HPP

#include <tools/tool.hpp>

class PlaneTool : public Tool {
  public:
    void onDragStart(glm::ivec2 start) override;
    void onDrawUpdate(glm::ivec2 current) override;
    void onDragEnd() override;
};

#endif