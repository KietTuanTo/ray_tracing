#pragma once

#include "vec3/color.h"
#include "vec3/vec3.h"
#include "ray/ray.h"
#include <cmath>
#include <iostream>
#include <limits>
#include <memory>

namespace ray_common {
const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

inline double degrees_to_radians(double degrees) {
    return degrees * pi / 180.0;
}
}
