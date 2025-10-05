# Python module shared library dependencies

__tl;dr:__ Python has trouble finding our module's local transitive depencencies,
so this is a workaround to make it work for now.

## The workaround

For now we're copying the following built shared libraries here `manually`:

```
libspdlogd.so.1.15.3
libspdlog.so.1.15
libvips.so.42
libvips.so.42.20.0
```

In our CMake build process we set an `RPATH` variable on the `vips_py` target
so that the built library first looks for its own shared library dependencies here.
This is necessary so that when Python loads the shared libary for the `vips_py`
module it can find the shared objects for its locally-built, non-system dependencies.

We've added a convenience script `get-libs.sh` to make these copies after
the CMake build is complete, that is run by `make build`.

__spdlog library name issue:__

Note that we have to rename the spdlog shared library to make the linker
happy when loading it as a dependency of the Python module.

```
libspdlogd.so.1.15 -> libspdlog.so.1.15
```

## TODO

There is surely an official way to handle this with PyBind11 and/or
one of the Pip build backends. We should find that out and implement it.
Similarly we should figure out the issue with the spdlog object name. In
theory, there should be processes in the various build systems to handle
these issues. If so, we just need to do some research to find them.
