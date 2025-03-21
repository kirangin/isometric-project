#ifndef TOOL_HPP
#define TOOL_HPP

#include <glm/glm.hpp>
#include <vector>

class Tool {
  public:
    enum class Primitive { Plane };

    Tool() = default;
    virtual ~Tool() = default;

    virtual void onDragStart(glm::ivec2 start) = 0;
    virtual void onDrawUpdate(glm::ivec2 current) = 0;
    virtual void onDragEnd() = 0;
    
    const std::vector<glm::ivec2>& getPreviewTiles() const;

  protected:
    std::vector<glm::ivec2> m_previewTiles;
    glm::ivec2 m_start;
};

#endif