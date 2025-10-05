/**
 * A basic test of the libvips C API.
 * Modified from the use-vips-func.c example file.
 */

#include <spdlog/spdlog.h>
#include <vips/vips.h>

#include <string>

enum class Operation {
    Gamma,
    Invert,
    None
};

constexpr Operation getTestOp() {
    constexpr Operation testOp = Operation::Gamma;
    return testOp;
}

int main(int argc, char **argv) {
    std::string imageFile = "images/pexels-stijn-dijkstra-1306815-29988776.jpg";
    std::string outptFile = "images/test_out.jpg";

    VipsImage *in;
    double mean;
    VipsImage *out;

    // Must initialize vips framework.
    if (VIPS_INIT(argv[0])) {
        vips_error_exit("Failed to initialize vips.", NULL);
    }
    if (!(in = vips_image_new_from_file(imageFile.c_str(), NULL))) {
        vips_error_exit("Failed to read image file: %s", imageFile.c_str(), NULL);
    }
    spdlog::info("image width = {:d}", vips_image_get_width(in));

    if (vips_avg(in, &mean, NULL)) {
        vips_error_exit(NULL);
    }
    spdlog::info("mean pixel value = {:g}", mean);

    int opResult = 0;
    switch (getTestOp()) {
        case Operation::Gamma: {
            constexpr gdouble gamma = 2.4;
            opResult = vips_gamma(in, &out, "exponent", gamma, NULL);
            break;
        }

        case Operation::Invert: {
            opResult = vips_invert(in, &out, NULL);
            break;
        }

        default: {
            spdlog::debug("Invalid test operation setting. No operation will be performed.");
            break;
        }
    }
    if (opResult != 0 || out == nullptr) {
        vips_error_exit("Image operation failed.", NULL);
    }

    g_object_unref(in);
    if (vips_image_write_to_file(out, outptFile.c_str(), NULL)) {
        vips_error_exit("Failed to write image file: %s", outptFile.c_str(), NULL);
    }
    g_object_unref(out);
    spdlog::info("Processed image written to: {}", outptFile);

    return 0;
}
