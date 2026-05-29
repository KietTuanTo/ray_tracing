#pragma once

#include "common/common.h"
#include "hittable/hittable.h"

class camera {
public:
    double aspect_ratio_ = 1.0;
    int image_width_ = 100;
    int samples_per_pixel_ = 10;

    void render(const hittable& world);
    
private:
    void initialize();
    color ray_color(const ray& r, const hittable& world) const;
    ray get_ray(int i, int j) const;
    vec3 sample_square() const;

    int image_height_;
    double pixel_samples_scale_;
    point3 centre_;
    point3 upper_left_pixel_;
    vec3 pixel_x_delta_;
    vec3 pixel_y_delta_;
};