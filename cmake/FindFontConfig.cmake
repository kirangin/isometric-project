# FindFontconfig.cmake
#
# Finds the Fontconfig library using pkg-config.
#
# This will define the following variables:
#
#   Fontconfig_FOUND        - True if Fontconfig is found.
#   Fontconfig_INCLUDE_DIRS - Include directories for Fontconfig headers.
#   Fontconfig_LIBRARIES    - Libraries to link against for Fontconfig.
#   Fontconfig_VERSION      - Version of Fontconfig found.
#
# This module relies on pkg-config to locate Fontconfig. If pkg-config is not
# available or Fontconfig is not found, Fontconfig_FOUND will be set to FALSE.

# Attempt to find pkg-config quietly
find_package(PkgConfig QUIET)

if(PKG_CONFIG_FOUND)
  # Use pkg-config to find the fontconfig library quietly
  pkg_check_modules(PC_FONTCONFIG QUIET fontconfig)
endif()

if(PC_FONTCONFIG_FOUND)
  # Set the standard CMake variables using pkg-config results
  set(Fontconfig_INCLUDE_DIRS ${PC_FONTCONFIG_INCLUDE_DIRS})
  set(Fontconfig_LIBRARIES ${PC_FONTCONFIG_LIBRARIES})
  set(Fontconfig_VERSION ${PC_FONTCONFIG_VERSION})
endif()

# Include the standard CMake module to handle find_package arguments
include(FindPackageHandleStandardArgs)

# Handle the QUIET, REQUIRED, and version arguments, and set Fontconfig_FOUND
find_package_handle_standard_args(Fontconfig
  REQUIRED_VARS Fontconfig_INCLUDE_DIRS Fontconfig_LIBRARIES
  VERSION_VAR Fontconfig_VERSION
)