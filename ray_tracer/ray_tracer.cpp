#include "common/common.h"
#include "hittable/hittable.h"
#include "hittable/hittable_list/hittable_list.h"
#include "hittable/sphere/sphere.h"

color ray_color(const ray& r, const hittable& world) {
    hit_record rec;
    if (world.hit(r, 0, rt::infinity, rec)) {
        return 0.5 * color(rec.normal + color(1, 1, 1));
    }

    vec3 unit_direction = unit_vector(r.direction());
    auto a = 0.5 * (unit_direction.y() + 1.0);
    return (1 - a) * color(1, 1, 1) + a * color(0.5, 0.7, 1);
}

int main() {

    auto aspect_ratio = 16.0 / 9.0;
    int image_width = 400;
    int image_height = int(image_width / aspect_ratio);
    image_height = image_height < 1 ? 1 : image_height;

    auto focal_length = 1.0;
    auto viewport_height = 2.0;
    auto viewport_width = viewport_height * ((double) image_width / (double) image_height);
    auto camera_centre = point3(0, 0, 0);

    auto viewport_x_vec = vec3(viewport_width, 0, 0);
    auto viewport_y_vec = vec3(0, -viewport_height, 0);
    auto pixel_x_delta = viewport_x_vec / image_width;
    auto pixel_y_delta = viewport_y_vec / image_height;

    auto viewport_upper_left = (
        camera_centre -
        vec3(0, 0, focal_length) -
        (viewport_x_vec / 2) -
        (viewport_y_vec / 2)
    );

    auto upper_left_pixel = viewport_upper_left + 0.5 * (pixel_x_delta + pixel_y_delta);
    
    hittable_list world;
    world.add(std::make_shared<sphere>(point3(0, 0, -1), 0.5));
    world.add(std::make_shared<sphere>(point3(0, -100.5, -1), 100));
    
    // Render image:
    std::cout << "P3\n" << image_width << " " << image_height << "\n255\n";

    for (int j = 0; j < image_height; ++j) {
        std::clog << "\rScanlines remaining: " << (image_height - j) << " " << std::flush;
        for (int i = 0; i < image_width; ++i) {
            auto pixel_centre = upper_left_pixel + (i * pixel_x_delta) + (j * pixel_y_delta);
            auto ray_direction = pixel_centre - camera_centre;
            ray r(camera_centre, ray_direction);
            auto pixel_colour = ray_color(r, world);
            write_colour(std::cout, pixel_colour);
        }
    }

    std::clog << "\rDone.           \n";
}