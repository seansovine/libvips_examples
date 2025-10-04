/**
 * A basic test of the libvips C++ API.
 * Modified from the avg.cpp example file.
 */

// Optional:
// #define DEBUG

#include <spdlog/spdlog.h>
#include <vips/vips8>

#include <string>

using namespace vips;

int main(int argc, char **argv) {
    // Must initialize vips framework.
    if (vips_init(argv[0])) {
        vips_error_exit(NULL);
    }

    std::string imageFile = "images/pexels-stijn-dijkstra-1306815-29988776.jpg";
    VImage in = VImage::new_from_file(imageFile.c_str(),
                                      VImage::option()->set("access", VIPS_ACCESS_SEQUENTIAL));

    double avg = in.avg();
    spdlog::info("avg = {:g}", avg);

#ifdef PROPER_SHUTDOWN
    // Produces a lot of console output.
    vips_shutdown();
#endif

    return 0;
}
