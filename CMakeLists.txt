cmake_minimum_required (VERSION 2.6) 
project(UBE)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

# find_package(Gettext)
find_package(SDL)
find_package(SDL_image)
find_package(SDL_ttf)
find_package(Popt)
find_Package(Boost 1.16.0)

# set(LIBS ${LIBS} ${GETTEXT_LIBRARIES})
set(LIBS ${LIBS} ${SDL_LIBRARY})
set(LIBS ${LIBS} ${SDLIMAGE_LIBRARY})
set(LIBS ${LIBS} ${SDLTTF_LIBRARY})
set(LIBS ${LIBS} ${Popt_LIBRARIES})
set(LIBS ${LIBS} ${Boost_LIBRARIES})

include_directories(src ${SDL_INCLUDE_DIR} ${Popt_INCLUDE_DIR} ${Popt_INCLUDE_DIR})

set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} -DPREFIX=\\"${CMAKE_INSTALL_PREFIX}\\")

add_subdirectory(src)