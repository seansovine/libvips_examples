#include <glib-object.h>
#include <vips/vips.h>

#include <string>
// using namespace vips;

int main(int argc, char **argv) {
    std::string imageFile = "images/pexels-stijn-dijkstra-1306815-29988776.jpg";

    char filename[VIPS_PATH_MAX];
    char option_string[VIPS_PATH_MAX];
    vips__filename_split8(imageFile.c_str(), filename, option_string);

    if (!vips_existsf("%s", filename)) {
        vips_error("VipsForeignLoad", "file \"%s\" does not exist", filename);
        return -1;
    }
    if (vips_isdirf("%s", filename)) {
        vips_error("VipsForeignLoad", "\"%s\" is a directory", filename);
        return -1;
    }

    if (vips_init(argv[0]))
        vips_error_exit(NULL);

    GType type = g_type_from_name("VipsForeignLoad");

    // // vips_error_exit("\"%s\" is not a known file format", filename);
    const char *operation_name = vips_foreign_find_load(filename);

    vips_shutdown();
    return 0;

    // VipsImage *in;
    // double mean;
    // VipsImage *out;

    // if (!(in = vips_image_new_from_file(imageFile.c_str(), NULL)))
    //   vips_error_exit(NULL);

    // printf("image width = %d\n", vips_image_get_width(in));

    // if (vips_avg(in, &mean, NULL))
    //   vips_error_exit(NULL);

    // printf("mean pixel value = %g\n", mean);

    // /* generate photo nexative - replace with other vips_ funcs */
    // //   if (vips_invert(in, &out, NULL))
    // //     vips_error_exit(NULL);

    // gdouble gamma = 1.55;
    // if (vips_gamma(in, &out, gamma, NULL))
    //   vips_error_exit(NULL);

    // g_object_unref(in);

    // if (vips_image_write_to_file(out, outFile.c_str(), NULL))
    //   vips_error_exit(NULL);

    // g_object_unref(out);

    // return 0;
}
