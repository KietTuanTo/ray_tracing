#pragma once

#include "hittable/hittable.h"
#include "vec3/vec3.h"
#include "ray/ray.h"

class sphere : public hittable {
public:
    sphere(const point3& centre, double radius);

    bool hit(const ray& r, double ray_tmin, double ray_tmax, hit_record& rec) const override;

private:
    point3 centre_;
    double radius_;
};