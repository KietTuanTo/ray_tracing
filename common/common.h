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
#include <random>

namespace rt {

inline double degrees_to_radians(double degrees) {
    return degrees * rt::pi / 180.0;
}

inline double random_double() {
    std::mt19937 gen{};
    std::uniform_real_distribution<double> dis(0, 1.0);
    return dis(gen);
}

inline double random_double(double min, double max) {
    return min + (max - min) * random_double();
}

}
