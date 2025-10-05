# Test Programs for libvips

This is a project for testing out the use of the libvips image processing library.
We currently have one test program for the C API and another for the C++ API, in
the [src/](./src/) directory.

## Building

Our current build procedure:

```shell
# We build with bear to generate a compilation database for libvips.
cd libvips
bear -- meson setup build --reconfigure -Dcplusplus=true -Ddebug=true
bear -- meson compile -C build
cd ..

cmake -DCMAKE_BUILD_TYPE:STRING=Debug -DCMAKE_C_COMPILER:FILEPATH=/usr/bin/clang \
	-DCMAKE_CXX_COMPILER:FILEPATH=/usr/bin/clang++ -S . \
	-B ./build/Debug -G Ninja

# Symlink compilation database to location clangd expects it to be in.
ln -s build/Debug/compile_commands.json compile_commands.json

cmake --build ./build/Debug --config Debug --target all "-j `nproc`"
```

We may integrate the libvips build into the overall CMake build later.

## Compilation database

I'm not completely sure this is necessary, but to make sure clangd sees the
project information for the libvips library, which we build separately and
not with CMake, I do the following:

I copy all the command entries in the `thirdyparty/libvips/compile_commands.json`
and paste them into the `compile_commands.json` file that is symlinked into the
root directory in the build steps above. This allows clangd to parse the build
commands from both the main CMake build and the independent libvips build.

## Python module

There is a proof-of-concept Python module for libvips Python bindings using PyBind11,
defined [here](./src/vips-py/vips-module.cpp). It currently provides a single Python
function demonstrating that the library code can be called successfully from Python.

It can be built and tested with:

```shell
# Build the module.
make configure
make build
make pybuild

# Test it.
python test/vips_py_test.py
```
