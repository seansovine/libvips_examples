# Test Programs for libvips

This is a project for testing out the use of the libvips image processing library.
We currently have one test program for the C API and another for the C++ API,
defined in the [src/](./src/) directory.

See [Notes.md](./Notes.md) for notes on the current build process.

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
