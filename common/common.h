#pragma once

#include "constants.h"
#include "vec3/color.h"
#include "vec3/vec3.h"
#include "ray/ray.h"
#include "interval/interval.h"
#include <cmath>
#include <iostream>
#include <limits>
#include <memory>

namespace rt {

inline double degrees_to_radians(double degrees) {
    return degrees * rt::pi / 180.0;
}

}
