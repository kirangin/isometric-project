add_library(
  math STATIC 
  coordinates.cpp
  grid.cpp
)

target_include_directories(math PRIVATE 
  ${CMAKE_SOURCE_DIR}/src
  ${CMAKE_SOURCE_DIR}/extern/glm
)