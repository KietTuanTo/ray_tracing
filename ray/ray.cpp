#include "ray.h"

ray::ray() : origin_{0, 0, 0}, direction_(0, 0, 0) {};

ray::ray(const point3& origin, const vec3& direction) : origin_{origin}, direction_{direction} {};

const point3& ray::origin() const { return origin_; };

const vec3& ray::direction() const { return direction_; };

point3 ray::at(double t) const {
    return origin_ + t * direction_;
}