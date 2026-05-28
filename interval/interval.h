#pragma once

#include "common/common.h"

class interval {
public:
    interval();
    interval(double min, double max);

    double size() const;
    bool contains(double d) const;
    bool surrounds(double d) const;

    static const interval empty, universe;

private:
    double min_, max_;
};