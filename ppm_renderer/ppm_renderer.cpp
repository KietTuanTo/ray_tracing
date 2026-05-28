#include "vec3/vec3.h"
#include "vec3/color.h"
#include <iostream>

int main() {

    int image_width = 256;
    int image_height = 256;

    // Render image:

    std::cout << "P3\n" << image_width << " " << image_height << "\n255\n";

    for (int i = 0; i < image_width; ++i) {
        std::clog << "\rScanlines remaining: " << (image_height - i) << " " << std::flush;
        for (int j = 0; j < image_height; ++j) {
            auto pixel_colour = color((double) i / (image_width - 1), (double) j / (image_height - 1), 0);
            write_colour(std::cout, pixel_colour);
        }
    }

    std::clog << "\rDone.           \n";
}