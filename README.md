# Test Programs for libvips

We currently have one test program for the C API and another for the C++ API.

Our build commands:

```shell
# We build with bear to generate a compilation database for libvips.
cd libvips
bear -- meson setup build --reconfigure -Dcplusplus=true -Ddebug=true
bear -- meson compile -C build
cd ..

cmake -DCMAKE_BUILD_TYPE:STRING=Debug -DCMAKE_C_COMPILER:FILEPATH=/usr/bin/clang \
	-DCMAKE_CXX_COMPILER:FILEPATH=/usr/bin/clang++ -S /home/sean/Code_projects/libvips_test \
	-B /home/sean/Code_projects/libvips_test/build/Debug -G Ninja

# Simlink compilation database to location clangd expects it to be in.
ln -s build/Debug/compile_commands.json compile_commands.json

cmake --build /home/sean/Code_projects/libvips_test/build/Debug --config Debug --target all "-j 8"
```
