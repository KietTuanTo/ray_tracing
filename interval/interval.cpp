#include "interval.h"

interval::interval() : min_{rt::infinity}, max_{-rt::infinity} {};

interval::interval(double min, double max) : min_{min}, max_{max} {};

double interval::min() const { return min_; };

double interval::max() const { return max_; };

double interval::size() const { return max_ - min_; };

bool interval::contains(double d) const { return min_ <= d && d <= max_; };

bool interval::surrounds(double d) const { return min_ < d && d < max_; };

const interval interval::empty = interval();
const interval interval::universe = interval(-rt::infinity, rt::infinity);