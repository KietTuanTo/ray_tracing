#include <gtest/gtest.h>
#include "sphere.h"
#include "interval/interval.h"

const interval default_interval(0.001, 1000.0);

ray ray_along_z(point3 origin = {0, 0, 0}) {
    return ray(origin, vec3(0, 0, -1));
}

TEST(SphereConstruction, NegativeRadiusClampedToZero) {
    sphere s(point3(0, 0, -1), -5.0);
    hit_record rec;
    EXPECT_FALSE(s.hit(ray_along_z(), default_interval, rec));
}

TEST(SphereConstruction, ZeroRadiusNotHit) {
    sphere s(point3(0, 0, -1), 0.0);
    hit_record rec;
    EXPECT_FALSE(s.hit(ray_along_z(), default_interval, rec));
}

TEST(SphereHit, RayHitsSphereHeadOn) {
    sphere s(point3(0, 0, -1), 0.5);
    hit_record rec;
    EXPECT_TRUE(s.hit(ray_along_z(), default_interval, rec));
}

TEST(SphereHit, RayMissesSphere) {
    sphere s(point3(0, 0, -1), 0.5);
    ray r(point3(0, 0, 0), vec3(1, 0, 0));
    hit_record rec;
    EXPECT_FALSE(s.hit(r, default_interval, rec));
}

TEST(SphereHit, RayPointingAwayFromSphere) {
    sphere s(point3(0, 0, -1), 0.5);
    ray r(point3(0, 0, 0), vec3(0, 0, 1));
    hit_record rec;
    EXPECT_FALSE(s.hit(r, default_interval, rec));
}

TEST(SphereHit, HitOutsideTMaxReturnsFalse) {
    sphere s(point3(0, 0, -5), 0.5);
    hit_record rec;
    EXPECT_FALSE(s.hit(ray_along_z(), interval(0.001, 2.0), rec));
}

TEST(SphereHit, HitOutsideTMinReturnsFalse) {
    sphere s(point3(0, 0, -1), 0.5);
    hit_record rec;
    EXPECT_FALSE(s.hit(ray_along_z(), interval(2.0, 1000.0), rec));
}

TEST(SphereHit, HitWithinTRangeReturnsTrue) {
    sphere s(point3(0, 0, -1), 0.5);
    hit_record rec;
    EXPECT_TRUE(s.hit(ray_along_z(), default_interval, rec));
    EXPECT_TRUE(default_interval.surrounds(rec.t));
}

TEST(SphereHit, RecordTIsCorrect) {
    sphere s(point3(0, 0, -1), 0.5);
    hit_record rec;
    s.hit(ray_along_z(), default_interval, rec);
    EXPECT_NEAR(rec.t, 0.5, 1e-9);
}

TEST(SphereHit, RecordPointIsOnSphere) {
    sphere s(point3(0, 0, -1), 0.5);
    hit_record rec;
    s.hit(ray_along_z(), default_interval, rec);
    double dist = (rec.p - point3(0, 0, -1)).length();
    EXPECT_NEAR(dist, 0.5, 1e-9);
}

TEST(SphereHit, OutwardNormalPointsAwayFromCentre) {
    sphere s(point3(0, 0, -1), 0.5);
    hit_record rec;
    s.hit(ray_along_z(), default_interval, rec);
    EXPECT_NEAR(rec.normal.z(), 1.0, 1e-9);
}

TEST(SphereHit, RayFromOutsideFrontFace) {
    sphere s(point3(0, 0, -1), 0.5);
    hit_record rec;
    s.hit(ray_along_z(), default_interval, rec);
    EXPECT_TRUE(rec.front_face);
}

TEST(SphereHit, RayFromInsideBackFace) {
    sphere s(point3(0, 0, -1), 2.0);
    hit_record rec;
    s.hit(ray_along_z(), default_interval, rec);
    EXPECT_FALSE(rec.front_face);
}