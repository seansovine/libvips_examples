/**
 * Modified from the avg.cpp example file.
 */

// From example file; not sure if needed.
#define DEBUG

#include <vips/vips8>

#include <string>

using namespace vips;

int main(int argc, char **argv) {
    if (vips_init(argv[0])) {
        vips_error_exit(NULL);
    }

    std::string imageFile = "images/pexels-stijn-dijkstra-1306815-29988776.jpg";
    VImage in = VImage::new_from_file(imageFile.c_str(),
                                      VImage::option()->set("access", VIPS_ACCESS_SEQUENTIAL));

    double avg;
    avg = in.avg();
    printf("avg = %g\n", avg);

    // Produces a lot of console output.
    vips_shutdown();
    return 0;
}
