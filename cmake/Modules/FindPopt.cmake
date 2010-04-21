# - Try to find ImageMagick++
# Once done, this will define
#
#  Popt_FOUND - system has Popt
#  Popt_INCLUDE_DIRS - the Popt include directories
#  Popt_LIBRARIES - link these to use Popt

include(LibFindMacros)

# Dependencies
#libfind_package(Magick++ Magick)

# Use pkg-config to get hints about paths
#libfind_pkg_check_modules(Magick++_PKGCONF ImageMagick++)

# Include dir
# find_path(Magick++_INCLUDE_DIR
#   NAMES Magick++.h
#   PATHS ${Magick++_PKGCONF_INCLUDE_DIRS}
# )

find_path(Popt_INCLUDE_DIR
  NAMES popt.h
)

# Finally the library itself
# find_library(Magick++_LIBRARY
#   NAMES Magick++
#   PATHS ${Magick++_PKGCONF_LIBRARY_DIRS}
# )

find_library(Popt_LIBRARY
  NAMES popt
)

# Set the include dir variables and the libraries and let libfind_process do the rest.
# NOTE: Singular variables for this library, plural for libraries this this lib depends on.
# set(Magick++_PROCESS_INCLUDES Magick++_INCLUDE_DIR Magick_INCLUDE_DIRS)
# set(Magick++_PROCESS_LIBS Magick++_LIBRARY Magick_LIBRARIES)
# libfind_process(Magick++)

set(Popt_PROCESS_INCLUDES Popt_INCLUDE_DIR Magick_INCLUDE_DIRS)
set(Popt_PROCESS_LIBS Popt_LIBRARY Magick_LIBRARIES)
libfind_process(Popt)