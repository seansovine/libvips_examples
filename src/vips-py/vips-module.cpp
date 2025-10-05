/**
 * A proof of concept module for Python bindings to libvips.
 */

#include <pybind11/pybind11.h>
#include <spdlog/spdlog.h>
#include <vips/vips.h>

namespace py = pybind11;

void gamma_transform() {
    std::string imageFile = "images/pexels-stijn-dijkstra-1306815-29988776.jpg";
    std::string outptFile = "images/test_out.jpg";

    VipsImage *in;
    double mean;
    VipsImage *out;

    // Must initialize vips framework.
    if (VIPS_INIT("vips-py")) {
        vips_error_exit("Failed to initialize vips.", NULL);
    }

    spdlog::info("Reading test image: {}", imageFile);
    if (!(in = vips_image_new_from_file(imageFile.c_str(), NULL))) {
        vips_error_exit("Failed to read image file: %s", imageFile.c_str(), NULL);
    }
    spdlog::info("Image width = {:d}", vips_image_get_width(in));

    if (vips_avg(in, &mean, NULL)) {
        vips_error_exit(NULL);
    }
    spdlog::info("Mean pixel value = {:g}", mean);

    constexpr gdouble gamma = 1.55;
    int opResult = vips_gamma(in, &out, gamma, NULL);

    if (opResult != 0 || out == nullptr) {
        vips_error_exit("Image operation failed.", NULL);
    }

    g_object_unref(in);
    if (vips_image_write_to_file(out, outptFile.c_str(), NULL)) {
        vips_error_exit("Failed to write image file: %s", outptFile.c_str(), NULL);
    }
    g_object_unref(out);
    spdlog::info("Processed image written to: {}", outptFile);
}

PYBIND11_MODULE(vips_py, m, py::mod_gil_not_used()) {
    m.doc() = "WIP libvips bindings.";

    m.def("gamma_transform", &gamma_transform,
          "A function to test that we can call vips from Python.");
}
