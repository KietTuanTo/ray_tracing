#pragma once

#include "common/common.h"

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

    virtual bool hit(const ray& r, interval ray_t, hit_record& rec) const = 0;
};
