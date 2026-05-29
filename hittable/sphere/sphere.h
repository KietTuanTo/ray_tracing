#pragma once

#include "common/common.h"
#include "hittable/hittable.h"

class sphere : public hittable {
public:
    sphere(const point3& centre, double radius);

    bool hit(const ray& r, interval ray_t, hit_record& rec) const override;

private:
    point3 centre_;
    double radius_;
};