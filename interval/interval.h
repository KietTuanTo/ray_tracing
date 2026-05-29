#pragma once

#include "common/constants.h"

class interval {
public:
    interval();
    interval(double min, double max);

    double min() const;
    double max() const;

    double size() const;
    bool contains(double d) const;
    bool surrounds(double d) const;
    double clamp(double d) const;

    static const interval empty, universe;

private:
    double min_, max_;
};