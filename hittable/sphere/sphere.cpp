#include "sphere.h"

#include <algorithm>
#include <cmath>

sphere::sphere(const point3& centre, double radius) : centre_{centre}, radius_{std::max(radius, 0.0)} {};

bool sphere::hit(const ray& r, interval ray_t, hit_record& rec) const {
    vec3 origin_to_centre = centre_ - r.origin();
    auto a = r.direction().length_squared();
    auto h = dot(r.direction(), origin_to_centre);
    auto c = origin_to_centre.length_squared() - radius_ * radius_;
    auto discriminant = h * h - a * c;

    if (discriminant < 0) return false;
    
    auto sqrtd = std::sqrt(discriminant);
    auto root = (h - sqrtd) / a;
    if (root <= ray_t.min() || ray_t.max() <= root) {
        root = (h + sqrtd) / a;
        if (root <= ray_t.min() || ray_t.max() <= root) {
            return false;
        }
    }

    rec.t = root;
    rec.p = r.at(root);
    vec3 outward_normal_vec = (rec.p - centre_) / radius_;
    rec.set_face_normal(r, outward_normal_vec);

    return true;
};