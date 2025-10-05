cmake_minimum_required(VERSION 3.26)

project(
  VipsTest
  VERSION 0.0.1
  DESCRIPTION "Testing use of the libvips C++ library."
  LANGUAGES CXX C)

set(C_STANDARD 11)
set(CXX_STANDARD 20)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

### Build our own copy of libvips C++ bindings (for now).

add_subdirectory(libvips-cpp)

### Other third-party libraries.

# spdlog for logging.
set(SPDLOG_BUILD_SHARED ON)
add_subdirectory(thirdparty/spdlog)

# pybind11.
set(PYBIND11_FINDPYTHON ON)
add_subdirectory(thirdparty/pybind11)

### Build API test executables.

# Program to test the vips C API.
add_executable(test-c-api src/test-c-api.cpp)
target_link_libraries(
    test-c-api
  PUBLIC
    ${GOBJECT_LIBRARIES}
    vips-cpp
)

# Program to test the vips C++ API.
add_executable(test-cpp-api src/test-cpp-api.cpp)
target_link_libraries(
    test-cpp-api
  PUBLIC
    ${GOBJECT_LIBRARIES}
    vips-cpp
)

### pybind11 Python bindings.

pybind11_add_module(vips_py src/vips-py/vips-module.cpp)

target_link_libraries(
    vips_py
  PUBLIC
    ${GOBJECT_LIBRARIES}
    vips-cpp
    spdlog
)

# To let the Python module know where to find transitive
# dependency shared libraries that we have built locally.
#
# TODO: Find a better way to do this. At the least we
# could use proper install directories here.
set_target_properties(
    vips_py
    PROPERTIES
    INSTALL_RPATH
    "${CMAKE_SOURCE_DIR}/built-libs"
)

install(TARGETS vips_py DESTINATION .)
