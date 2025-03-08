# FindFreeType2.cmake
#
# This module attempts to find the FreeType2 library using pkg-config.
# If not found, it fetches and builds FreeType2 from GitHub.
# It defines:
# - FREETYPE2_FOUND: True if FreeType2 is found or successfully built
# - Freetype2::Freetype2: An imported target for modern CMake usage

# Prevent redefinition if the target already exists
if(TARGET Freetype2::Freetype2)
  set(FREETYPE2_FOUND TRUE)
  return()
endif()

# Try to find FreeType2 using pkg-config
find_package(PkgConfig QUIET)
if(PkgConfig_FOUND)
  pkg_check_modules(FREETYPE2 QUIET freetype2)
endif()

if(FREETYPE2_FOUND)
  # FreeType2 found via pkg-config; create an imported target
  message(STATUS "Found FreeType2 via pkg-config")
  add_library(Freetype2::Freetype2 INTERFACE IMPORTED)
  set_target_properties(Freetype2::Freetype2 PROPERTIES
    INTERFACE_INCLUDE_DIRECTORIES "${FREETYPE2_INCLUDE_DIRS}"
    INTERFACE_LINK_LIBRARIES "${FREETYPE2_LIBRARIES}"
  )
else()
  # FreeType2 not found; fetch and build it from GitHub
  message(STATUS "FreeType2 not found via pkg-config, fetching from GitHub")
  include(FetchContent)
  FetchContent_Declare(
    freetype
    GIT_REPOSITORY https://github.com/freetype/freetype.git
    GIT_TAG VER-2-10-4  # Specify a stable version; adjust as needed
  )
  # Optionally, set build options here (e.g., disable features)
  # set(FT_WITH_ZLIB OFF CACHE BOOL "" FORCE)
  FetchContent_MakeAvailable(freetype)
  # Alias the built freetype target to Freetype2::Freetype2
  add_library(Freetype2::Freetype2 ALIAS freetype)
endif()

# Set FREETYPE2_FOUND based on whether the target exists
if(TARGET Freetype2::Freetype2)
  set(FREETYPE2_FOUND TRUE)
else()
  set(FREETYPE2_FOUND FALSE)
endif()