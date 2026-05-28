#include <gtest/gtest.h>
#include <cmath>
#include "ray.h"

static constexpr double EPS = 1e-9;

static bool near_eq(const point3& a, const point3& b, double eps = EPS) {
    return std::abs(a.x() - b.x()) < eps &&
           std::abs(a.y() - b.y()) < eps &&
           std::abs(a.z() - b.z()) < eps;
}

TEST(RayConstruction, DefaultConstructor) {
    ray r;
    SUCCEED();
}

TEST(RayConstruction, ParameterisedConstructor) {
    const point3 origin(1.0, 2.0, 3.0);
    const vec3   direction(4.0, 5.0, 6.0);
    ray r(origin, direction);

    EXPECT_TRUE(near_eq(r.origin(),    origin));
    EXPECT_TRUE(near_eq(r.direction(), direction));
}

TEST(RayConstruction, ZeroOrigin) {
    const point3 origin(0.0, 0.0, 0.0);
    const vec3   direction(1.0, 0.0, 0.0);
    ray r(origin, direction);

    EXPECT_TRUE(near_eq(r.origin(), origin));
}

TEST(RayConstruction, ZeroDirection) {
    const point3 origin(1.0, 2.0, 3.0);
    const vec3   direction(0.0, 0.0, 0.0);
    ray r(origin, direction);

    EXPECT_TRUE(near_eq(r.direction(), direction));
}

TEST(RayConstruction, NegativeComponents) {
    const point3 origin(-1.0, -2.0, -3.0);
    const vec3   direction(-4.0, -5.0, -6.0);
    ray r(origin, direction);

    EXPECT_TRUE(near_eq(r.origin(),    origin));
    EXPECT_TRUE(near_eq(r.direction(), direction));
}

TEST(RayAccessors, OriginReturnsConstRef) {
    const ray r(point3(1, 2, 3), vec3(0, 0, 1));
    const point3& o = r.origin();       // must compile on a const ray
    EXPECT_TRUE(near_eq(o, point3(1, 2, 3)));
}

TEST(RayAccessors, DirectionReturnsConstRef) {
    const ray r(point3(0, 0, 0), vec3(0, 1, 0));
    const vec3& d = r.direction();      // must compile on a const ray
    EXPECT_TRUE(near_eq(d, vec3(0, 1, 0)));
}

TEST(RayAccessors, AccessorsDoNotMutateOrigin) {
    const point3 orig(7, 8, 9);
    ray r(orig, vec3(1, 0, 0));
    r.origin();                         // call accessor
    EXPECT_TRUE(near_eq(r.origin(), orig));
}

TEST(RayAccessors, AccessorsDoNotMutateDirection) {
    const vec3 dir(0, 0, -1);
    ray r(point3(0, 0, 0), dir);
    r.direction();
    EXPECT_TRUE(near_eq(r.direction(), dir));
}

TEST(RayAt, AtZeroReturnsOrigin) {
    const point3 origin(1.0, 2.0, 3.0);
    const vec3   direction(1.0, 0.0, 0.0);
    ray r(origin, direction);

    EXPECT_TRUE(near_eq(r.at(0.0), origin));
}

TEST(RayAt, AtOneReturnsOriginPlusDirection) {
    const point3 origin(1.0, 2.0, 3.0);
    const vec3   direction(4.0, 5.0, 6.0);
    ray r(origin, direction);

    const point3 expected(5.0, 7.0, 9.0);
    EXPECT_TRUE(near_eq(r.at(1.0), expected));
}

TEST(RayAt, AtNegativeT) {
    const point3 origin(0.0, 0.0, 0.0);
    const vec3   direction(1.0, 0.0, 0.0);
    ray r(origin, direction);

    EXPECT_TRUE(near_eq(r.at(-1.0), point3(-1.0, 0.0, 0.0)));
}

TEST(RayAt, AtFractionalT) {
    const point3 origin(0.0, 0.0, 0.0);
    const vec3   direction(2.0, 4.0, 6.0);
    ray r(origin, direction);

    EXPECT_TRUE(near_eq(r.at(0.5), point3(1.0, 2.0, 3.0)));
}

TEST(RayAt, AtLargeT) {
    const point3 origin(0.0, 0.0, 0.0);
    const vec3   direction(1.0, 0.0, 0.0);
    ray r(origin, direction);

    EXPECT_NEAR(r.at(1e6).x(), 1e6, 1e-3);
}

TEST(RayAt, AtWithNegativeOriginComponents) {
    const point3 origin(-5.0, -3.0, -1.0);
    const vec3   direction(1.0, 1.0, 1.0);
    ray r(origin, direction);

    EXPECT_TRUE(near_eq(r.at(3.0), point3(-2.0, 0.0, 2.0)));
}

TEST(RayAt, AtTwoEquidistantPoints) {
    ray r(point3(0, 0, 0), vec3(3.0, 4.0, 0.0));
    const point3 p1 = r.at(1.0);
    const point3 p2 = r.at(2.0);

    EXPECT_NEAR(p2.x() - p1.x(), 3.0, EPS);
    EXPECT_NEAR(p2.y() - p1.y(), 4.0, EPS);
    EXPECT_NEAR(p2.z() - p1.z(), 0.0, EPS);
}

TEST(RayAt, ParametricLinearityMultipleT) {
    const point3 origin(1.0, -2.0, 3.0);
    const vec3   dir(2.0, 3.0, -1.0);
    ray r(origin, dir);

    const double t1 = 1.5, t2 = 0.7;
    const point3 via_sum    = r.at(t1 + t2);
    const point3 via_offset = r.at(t1) + t2 * dir;

    EXPECT_TRUE(near_eq(via_sum, via_offset));
}

TEST(RayAt, NonUnitDirectionScalesCorrectly) {
    ray r1(point3(0, 0, 0), vec3(1.0, 0.0, 0.0));
    ray r2(point3(0, 0, 0), vec3(2.0, 0.0, 0.0));

    EXPECT_NEAR(r2.at(1.0).x(), 2.0 * r1.at(1.0).x(), EPS);
}

TEST(RayAt, VerySmallT) {
    ray r(point3(0, 0, 0), vec3(1, 0, 0));
    const double t = 1e-12;
    EXPECT_NEAR(r.at(t).x(), t, EPS);
}

TEST(RayAt, NaNPropagation) {
    ray r(point3(0, 0, 0), vec3(1, 0, 0));
    const double result = r.at(std::numeric_limits<double>::quiet_NaN()).x();
    EXPECT_TRUE(std::isnan(result));
}

TEST(RayAt, InfinityPropagation) {
    ray r(point3(0, 0, 0), vec3(1, 0, 0));
    const double result = r.at(std::numeric_limits<double>::infinity()).x();
    EXPECT_TRUE(std::isinf(result));
}

TEST(RayCopyAssign, CopyConstructor) {
    ray original(point3(1, 2, 3), vec3(4, 5, 6));
    ray copy(original);

    EXPECT_TRUE(near_eq(copy.origin(),    original.origin()));
    EXPECT_TRUE(near_eq(copy.direction(), original.direction()));
}

TEST(RayCopyAssign, CopyAssignment) {
    ray r1(point3(1, 0, 0), vec3(0, 1, 0));
    ray r2;
    r2 = r1;

    EXPECT_TRUE(near_eq(r2.origin(),    r1.origin()));
    EXPECT_TRUE(near_eq(r2.direction(), r1.direction()));
}

TEST(RayCopyAssign, CopiesAreIndependent) {
    ray r1(point3(1, 0, 0), vec3(0, 1, 0));
    ray r2 = r1;
    r2 = ray(point3(9, 9, 9), vec3(9, 9, 9));

    EXPECT_TRUE(near_eq(r1.origin(), point3(1, 0, 0)));
}