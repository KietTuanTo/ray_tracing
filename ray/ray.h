#pragma once

#include "vec3/vec3.h"

class ray {
public:
    ray();
    ray(const point3& origin, const vec3& direction);

    const point3& origin() const;
    const point3& direction() const;

    point3 at(double t);

private:
    point3 origin_;
    vec3 direction_;
};