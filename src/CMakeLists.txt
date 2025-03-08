add_executable(isometric 
  ui/base.cpp
  ui/button.cpp
  ui/manager.cpp
  ui/layout.cpp
  ui/hbox_layout.cpp
  ui/vbox_layout.cpp
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
)

target_link_libraries(isometric PRIVATE ${GLFW_LIBRARIES} ${SKIA_LIBRARIES} ${FREETYPE2_LIBRARIES} ${Fontconfig_LIBRARIES} GL pthread dl X11)