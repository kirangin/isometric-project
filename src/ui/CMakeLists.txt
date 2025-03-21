add_library(ui STATIC 
  base.cpp
  button.cpp
  manager.cpp
  layout.cpp
  hbox_layout.cpp
  vbox_layout.cpp
  toolbar.cpp
  input.cpp
)

target_include_directories(
  ui PRIVATE 
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

target_link_libraries(ui PRIVATE ${GLFW_LIBRARIES} ${SKIA_LIBRARIES} ${FREETYPE2_LIBRARIES} ${Fontconfig_LIBRARIES} glm::glm GL pthread dl X11)