cmake_minimum_required(VERSION 3.26)

project(
  VipsTest
  VERSION 0.0.1
  DESCRIPTION "Testing use of the libvips C++ library."
  LANGUAGES CXX C)

set(C_STANDARD 11)
set(CXX_STANDARD 20)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

### Dependencies added with pkg-config.

set(ENV{PKG_CONFIG_PATH} "$ENV{PKG_CONFIG_PATH}:${CMAKE_SOURCE_DIR}/thirdparty/libvips/build/meson-private")
find_package(PkgConfig REQUIRED)

# pkg_search_module(GLIB REQUIRED glib-2.0)
# include_directories(${GLIB_INCLUDE_DIRS})
# link_directories(${GLIB_LIBRARY_DIRS})

pkg_search_module(GOBJECT REQUIRED gobject-2.0)
include_directories(${GOBJECT_INCLUDE_DIRS})
link_directories(${GOBJECT_LIBRARY_DIRS})

pkg_search_module(VIPS REQUIRED vips)
include_directories(${VIPS_INCLUDE_DIRS})
link_directories(${VIPS_LIBRARY_DIRS})

message(DEBUG "vips-cpp include paths: ${VIPS_INCLUDE_DIRS}")

### Other third-party libraries.

# spdlog for logging.
set(SPDLOG_BUILD_SHARED ON)
add_subdirectory(thirdparty/spdlog)

###

# Source files for vips-cpp library.
file(
	GLOB LIBVIPS_CPP_SOURCES
	"${CMAKE_SOURCE_DIR}/thirdparty/libvips/build/libvips/include/version.h"
	"${CMAKE_SOURCE_DIR}/libvips-cpp/*.cpp"
	"${CMAKE_SOURCE_DIR}/libvips-cpp/include/*."
	"${CMAKE_SOURCE_DIR}/libvips-cpp/include/vips/vips8"
)

# Build shared library from vips cpp bindings.
add_library(
	libvips-cpp
		SHARED
	${LIBVIPS_CPP_SOURCES}
)
target_include_directories(
	libvips-cpp
		PUBLIC
	"${CMAKE_SOURCE_DIR}/thirdparty/libvips/libvips/include"
	"${CMAKE_SOURCE_DIR}/thirdparty/libvips/build/libvips/include"
	"${CMAKE_SOURCE_DIR}/libvips-cpp/include"
	"${CMAKE_SOURCE_DIR}/libvips-cpp/generated"
	"${VIPS_INCLUDE_DIRS}"
)
target_link_libraries(
	libvips-cpp
		PUBLIC
	"${CMAKE_SOURCE_DIR}/thirdparty/libvips/build/libvips/libvips.so"
	spdlog
)

# Program to test the vips C API.
add_executable(test-c-api src/test-c-api.cpp)
target_link_libraries(
	test-c-api
		PUBLIC
	${GOBJECT_LIBRARIES}
	libvips-cpp
)

# Program to test the vips C++ API.
add_executable(test-cpp-api src/test-cpp-api.cpp)
target_link_libraries(
	test-cpp-api
		PUBLIC
	${GOBJECT_LIBRARIES}
	libvips-cpp
)
