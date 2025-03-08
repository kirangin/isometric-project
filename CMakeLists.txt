cmake_minimum_required(VERSION 3.5)

project(isometric VERSION 0.1
                  DESCRIPTION "A simple isometric sprite creator"
                  LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

# Set the path to your Skia installation
set(SKIA_ROOT "$ENV{HOME}/deps/skia")

# Add cmake modules
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

# Find the GLFW library, marked as required
find_package(GLFW REQUIRED)
find_package(Skia REQUIRED)
find_package(FreeType2 REQUIRED)

add_subdirectory(src)
