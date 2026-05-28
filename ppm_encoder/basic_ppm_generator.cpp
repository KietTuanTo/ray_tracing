#include <iostream>

int main() {

    int image_width = 256;
    int image_height = 256;

    // Render image:

    std::cout << "P3\n" << image_width << " " << image_height << "\n255\n";

    for (int i = 0; i < image_width; ++i) {
        std::clog << "\rScanlines remaining: " << (image_height - i) << " " << std::flush;
        for (int j = 0; j < image_height; ++j) {
            auto r = (double) i / (image_width - 1);
            auto g = (double) j / (image_height - 1);

            int ir = int(255.999 * r);
            int ig = int(255.999 * g);
            int ib = 0;

            std::cout << ir << " " << ig << " " << ib << '\n';
        }
    }

    std::clog << "\rDone.           \n";
}