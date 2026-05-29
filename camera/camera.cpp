#include "camera.h"

void camera::render(const hittable& world) {
    initialize();

    std::cout << "P3\n" << image_width_ << " " << image_height_ << "\n255\n";

    for (int j = 0; j < image_height_; ++j) {
        std::clog << "\rScanlines remaining: " << (image_height_ - j) << " " << std::flush;
        for (int i = 0; i < image_width_; ++i) {
            auto pixel_centre = upper_left_pixel_ + (i * pixel_x_delta_) + (j * pixel_y_delta_);
            auto ray_direction = pixel_centre - centre_;
            ray r(centre_, ray_direction);
            auto pixel_colour = ray_color(r, world);
            write_colour(std::cout, pixel_colour);
        }
    }

    std::clog << "\rDone.           \n";    
}

void camera::initialize() {    
    centre_ = point3(0, 0, 0);
    image_height_ = int(image_width_ / aspect_ratio_);
    image_height_ = image_height_ < 1 ? 1 : image_height_;

    auto focal_length = 1.0;
    auto viewport_height = 2.0;
    auto viewport_width = viewport_height * ((double) image_width_ / image_height_);

    auto viewport_x_vec = vec3(viewport_width, 0, 0);
    auto viewport_y_vec = vec3(0, -viewport_height, 0);
    
    pixel_x_delta_ = viewport_x_vec / image_width_;
    pixel_y_delta_ = viewport_y_vec / image_height_;

    auto viewport_upper_left = (
        centre_ -
        vec3(0, 0, focal_length) -
        (viewport_x_vec / 2) -
        (viewport_y_vec / 2)
    );

    upper_left_pixel_ = viewport_upper_left + 0.5 * (pixel_x_delta_ + pixel_y_delta_);
}

color camera::ray_color(const ray& r, const hittable& world) const {
    hit_record rec;
    if (world.hit(r, interval(0, rt::infinity), rec)) {
        return 0.5 * (rec.normal + color(1, 1, 1));
    }

    vec3 unit_direction = unit_vector(r.direction());
    auto a = 0.5 * (unit_direction.y() + 1.0);
    return (1 - a) * color(1, 1, 1) + a * color(0.5, 0.7, 1);
}
