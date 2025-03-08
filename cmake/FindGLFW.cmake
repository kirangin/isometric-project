# GLFW.cmake

# Prevent redefinition if GLFW::glfw target already exists
if(TARGET GLFW::glfw)
  return()
endif()

# Use pkg-config to check for GLFW
include(FindPkgConfig)
pkg_check_modules(GLFW QUIET glfw3)

if(GLFW_FOUND)
  # If found via pkg-config, create an imported target
  message(STATUS "Found GLFW via pkg-config")
  add_library(GLFW::glfw INTERFACE IMPORTED)
  set_target_properties(GLFW::glfw PROPERTIES
    INTERFACE_INCLUDE_DIRECTORIES "${GLFW_INCLUDE_DIRS}"
    INTERFACE_LINK_LIBRARIES "${GLFW_LIBRARIES}"
  )
else()
  # If not found, fetch GLFW from GitHub using FetchContent
  message(STATUS "GLFW not found via pkg-config, fetching from GitHub")
  include(FetchContent)
  FetchContent_Declare(
    glfw
    GIT_REPOSITORY https://github.com/glfw/glfw.git
    GIT_TAG 3.3.4  # Specify the desired version here
  )
  # Configure GLFW build options to minimize unnecessary components
  set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "Build GLFW examples")
  set(GLFW_BUILD_TESTS OFF CACHE BOOL "Build GLFW tests")
  set(GLFW_BUILD_DOCS OFF CACHE BOOL "Build GLFW documentation")
  set(GLFW_INSTALL OFF CACHE BOOL "Generate installation target")
  FetchContent_MakeAvailable(glfw)
  # Alias the built glfw target to GLFW::glfw
  add_library(GLFW::glfw ALIAS glfw)
endif()

# Indicate that GLFW is available
set(GLFW_FOUND TRUE)