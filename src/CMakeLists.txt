add_executable(isometric 
  render/renderer.cpp
  render/cube.cpp
  export/png.cpp

  core/application.cpp
  core/render_context.cpp
  core/window.cpp
  core/event_handler.cpp
  tools/tool.cpp
  tools/plane_tool.cpp
  main.cpp
)

target_include_directories(
  isometric PRIVATE 
  ${CMAKE_SOURCE_DIR}/src 
  ${GLFW_INCLUDE_DIRS}
  ${SKIA_INCLUDE_DIR}

  # This is important because I don't to write "include/core" 
  # in my code but Skia's code does. 
  ${SKIA_INCLUDE_DIR}/../
  ${FREETYPE2_INCLUDE_DIRS}
  ${Fontconfig_INCLUDE_DIRS}

  # Stb image and GLM
  ${CMAKE_SOURCE_DIR}/extern/glm
  ${CMAKE_SOURCE_DIR}/extern/stb
)

add_subdirectory(math)
add_subdirectory(ui)

target_link_libraries(isometric PRIVATE math ui ${SKIA_LIBRARIES} ${FREETYPE2_LIBRARIES} ${Fontconfig_LIBRARIES})