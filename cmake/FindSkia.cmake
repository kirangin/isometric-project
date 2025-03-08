# FindSkia.cmake
# This module locates a pre-compiled Skia library and creates an imported target Skia::skia.

# If the Skia::skia target already exists, assume Skia is found and exit early
if(TARGET Skia::skia)
  set(SKIA_FOUND TRUE)
  return()
endif()

# Find the include directory by looking for a key header file (SkCanvas.h)
find_path(SKIA_INCLUDE_DIR
  NAMES core/SkCanvas.h
  PATH_SUFFIXES include
  HINTS ${SKIA_ROOT}
)

# Define the list of Skia libraries to find (adjust this based on your Skia build)
set(SKIA_LIB_NAMES skia skshaper skresources)

# Search for each library in the list
foreach(lib ${SKIA_LIB_NAMES})
  find_library(SKIA_${lib}_LIBRARY
    NAMES ${lib}
    PATH_SUFFIXES out/Release lib
    HINTS ${SKIA_ROOT}
  )
  if(SKIA_${lib}_LIBRARY)
    list(APPEND SKIA_LIBRARIES ${SKIA_${lib}_LIBRARY})
  else()
    message(WARNING "Could not find Skia library: ${lib}")
  endif()
endforeach()

# Determine if Skia was found (requires both include directory and at least one library)
if(SKIA_INCLUDE_DIR AND SKIA_LIBRARIES)
  set(SKIA_FOUND TRUE)
  # Create an interface imported target for Skia
  add_library(Skia::skia INTERFACE IMPORTED)
  set_target_properties(Skia::skia PROPERTIES
    INTERFACE_INCLUDE_DIRECTORIES "${SKIA_INCLUDE_DIR}"
    INTERFACE_LINK_LIBRARIES "${SKIA_LIBRARIES}"
  )
else()
    set(SKIA_FOUND FALSE)
endif()

# Report the result (optional, for debugging)
if(SKIA_FOUND)
  message(STATUS "Found Skia: include=${SKIA_INCLUDE_DIR}, libraries=${SKIA_LIBRARIES}")
else()
  message(WARNING "Skia not found. Please set SKIA_ROOT to the Skia directory.")
endif()