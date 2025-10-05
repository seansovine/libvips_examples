### Dependencies added with pkg-config.

# We require libvips to have already been separately built (for now).
if(NOT EXISTS "${CMAKE_SOURCE_DIR}/thirdparty/libvips/build/libvips/libvips.so")
    message(FATAL_ERROR "Did not find libvips shared object. Has thirdparty/libvips been built?")
endif()

# To get dependencies of externally built libvips.
set(ENV{PKG_CONFIG_PATH} "$ENV{PKG_CONFIG_PATH}:${CMAKE_SOURCE_DIR}/thirdparty/libvips/build/meson-private")

find_package(PkgConfig REQUIRED)

pkg_search_module(GOBJECT REQUIRED gobject-2.0)
include_directories(${GOBJECT_INCLUDE_DIRS})
link_directories(${GOBJECT_LIBRARY_DIRS})

pkg_search_module(VIPS REQUIRED vips)
include_directories(${VIPS_INCLUDE_DIRS})
link_directories(${VIPS_LIBRARY_DIRS})

message(DEBUG "vips-cpp include paths: ${VIPS_INCLUDE_DIRS}")

### Build our local vips-cpp.

file(
    GLOB LIBVIPS_CPP_HEADERS
    "${CMAKE_SOURCE_DIR}/thirdparty/libvips/build/libvips/include/version.h"
    "${CMAKE_SOURCE_DIR}/libvips-cpp/include/*.h"
    "${CMAKE_SOURCE_DIR}/libvips-cpp/include/vips/vips8"
)

file(
    GLOB LIBVIPS_CPP_SOURCES
    "${CMAKE_SOURCE_DIR}/libvips-cpp/*.cpp"
)

# Build shared library for vips cpp bindings.
add_library(
    vips-cpp
  SHARED
    ${LIBVIPS_CPP_HEADERS}
    ${LIBVIPS_CPP_SOURCES}
)

target_include_directories(
    vips-cpp
  PUBLIC
    "${CMAKE_SOURCE_DIR}/thirdparty/libvips/libvips/include"
    "${CMAKE_SOURCE_DIR}/thirdparty/libvips/build/libvips/include"
    "${CMAKE_SOURCE_DIR}/libvips-cpp/include"
    "${CMAKE_SOURCE_DIR}/libvips-cpp/generated"
    "${VIPS_INCLUDE_DIRS}"
)

target_link_libraries(
    vips-cpp
  PUBLIC
    "${CMAKE_SOURCE_DIR}/thirdparty/libvips/build/libvips/libvips.so"
    spdlog
)
