/**
 * A basic test of the libvips C++ API.
 * Modified from the avg.cpp example file.
 */

// Optional:
// #define DEBUG

#include <spdlog/spdlog.h>
#include <vips/vips8>

#include <iostream>

using namespace vips;

int main(int argc, char **argv) {
    // Must initialize vips framework.
    if (vips_init(argv[0])) {
        vips_error_exit(NULL);
    }

    std::string imageFile = "images/pexels-stijn-dijkstra-1306815-29988776.jpg";

    try {
        // Load the image
        VImage in = VImage::new_from_file(imageFile.c_str(),
                                          VImage::option()->set("access", VIPS_ACCESS_SEQUENTIAL));

        // NOTE: In "sequential mode" we can only perform one operation
        // before writing the image back out, because operations are delayed.
        //
        // SEE: https://stackoverflow.com/questions/72742058/
        //
        // double avg = in.avg();
        // spdlog::info("avg = {:g}", avg);

        VImage out = in.gamma(VImage::option()->set("exponent", 0.8));
        out.write_to_file("images/gamma_output.jpg");
    } catch (const VError &e) {
        std::cout << e.what() << std::endl;
        return 1;
    }

#ifdef PROPER_SHUTDOWN
    // Produces a lot of console output.
    vips_shutdown();
#endif

    return 0;
}
