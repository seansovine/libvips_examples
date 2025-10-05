# Build notes

## Building

Our current build procedure:

```shell
# Get thirdparty submodules.
git submodule update --init --recursive

# We build with bear to generate a compilation database for libvips.
cd libvips
bear -- meson setup build --reconfigure -Dcplusplus=true -Ddebug=true --buildtype=debug
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

We've also found it useful to uncomment the line

```c
#define VIPS_DEBUG
```

in `operation.c` when tracing through runs of the vips code.

## Compilation database

I'm not completely sure this is necessary, but to make sure clangd sees the
project information for the libvips library, which we build separately and
not with CMake, I do the following:

I copy all the command entries in the `thirdyparty/libvips/compile_commands.json`
and paste them into the `compile_commands.json` file that is symlinked into the
root directory in the build steps above. This allows clangd to parse the build
commands from both the main CMake build and the independent libvips build.
