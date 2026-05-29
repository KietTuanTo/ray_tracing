#include "color.h"
#include "interval/interval.h"

void write_colour(std::ostream& out, const color& pixel_colour) {
    auto r = pixel_colour.x();
    auto g = pixel_colour.y();
    auto b = pixel_colour.z();

    static const interval intensity(0, 0.999);

    int rbyte = int(255.999 * intensity.clamp(r));
    int gbyte = int(255.999 * intensity.clamp(g));
    int bbyte = int(255.999 * intensity.clamp(b));

    out << rbyte << " " << gbyte << " " << bbyte << '\n';
}