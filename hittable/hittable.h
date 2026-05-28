#pragma once

#include "ray/ray.h"
#include "vec3/vec3.h"

struct hit_record {
    point3 p;
    vec3 normal;
    double t;
    bool front_face;

    void set_face_normal(const ray& r, const vec3& outward_normal_vec) {
        front_face = dot(r.direction(), outward_normal_vec) < 0;
        normal = front_face ? outward_normal_vec : -outward_normal_vec;
    }
};

class hittable {
public:
    virtual ~hittable() = default;

    virtual bool hit(const ray& r, double ray_tmin, double ray_tmax, hit_record& rec) const = 0;
};
