configure:
	@cmake -DCMAKE_BUILD_TYPE:STRING=Debug -DCMAKE_C_COMPILER:FILEPATH=/usr/bin/clang \
		-DCMAKE_CXX_COMPILER:FILEPATH=/usr/bin/clang++ -S . \
		-B ./build/Debug -G Ninja

.PHONY: build

build:
	@# Note: This assumes that libvips has already been built. See Notes.md.
	@cmake --build ./build/Debug --config Debug --target all "-j `nproc`"

	@# TODO: Replace this with an "official" process, if one exists.
	built-libs/get-libs.sh

clean:
	rm -rf build/

c_test:
	build/Debug/test-c-api

cpp_test:
	build/Debug/test-cpp-api

pybuild:
	@pip install --force-reinstall .

pytest:
	@python test/vips_py_test.py
