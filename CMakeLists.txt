cmake_minimum_required (VERSION 2.6) 
project(UBE)

set(VERSION 0.4.0-dev)
set(PACKAGE ube)

add_definitions(-Wall -Werror)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

find_package(Gettext)
find_package(SDL)
find_package(SDL_image)
find_package(SDL_ttf)
find_package(Popt)
find_Package(Boost 1.16.0)

set(LIBS ${LIBS} ${SDL_LIBRARY})
set(LIBS ${LIBS} ${SDLIMAGE_LIBRARY})
set(LIBS ${LIBS} ${SDLTTF_LIBRARY})
set(LIBS ${LIBS} ${Popt_LIBRARIES})
set(LIBS ${LIBS} ${Boost_LIBRARIES})

include_directories(src ${SDL_INCLUDE_DIR} ${Popt_INCLUDE_DIR} ${Popt_INCLUDE_DIR})

include_directories (${UBE_SOURCE_DIR}/src ${UBE_BINARY_DIR}/src)

set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} -DPREFIX=\\"${CMAKE_INSTALL_PREFIX}\\")

add_subdirectory(data)
add_subdirectory(src)

option (ENABLE_NLS "Native Language Support" ON)

configure_file (${UBE_SOURCE_DIR}/src/config.h.cmake ${UBE_BINARY_DIR}/src/config.h)

GETTEXT_CREATE_TRANSLATIONS(po/ube.pot ALL po/fr.po)
