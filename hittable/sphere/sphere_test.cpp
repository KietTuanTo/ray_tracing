#include <gtest/gtest.h>
#include "sphere.h"

ray ray_along_z(point3 origin = {0, 0, 0}) {
    return ray(origin, vec3(0, 0, -1));
}

TEST(SphereHit, RayHitsSphereHead0n) {
    sphere s(point3(0, 0, -1), 0.5);
    hit_record rec;
    EXPECT_TRUE(s.hit(ray_along_z(), 0.001, 1000.0, rec));
}

TEST(SphereHit, RayMissesSphere) {
    sphere s(point3(0, 0, -1), 0.5);
    ray r(point3(0, 0, 0), vec3(1, 0, 0)); // pointing away in x
    hit_record rec;
    EXPECT_FALSE(s.hit(r, 0.001, 1000.0, rec));
}

TEST(SphereHit, RayPointingAwayFromSphere) {
    sphere s(point3(0, 0, -1), 0.5);
    ray r(point3(0, 0, 0), vec3(0, 0, 1)); // pointing +z, sphere is at -z
    hit_record rec;
    EXPECT_FALSE(s.hit(r, 0.001, 1000.0, rec));
}

TEST(SphereHit, HitOutsideTMaxReturnsFalse) {
    sphere s(point3(0, 0, -5), 0.5);
    hit_record rec;
    // sphere is at t≈4.5, tmax=2 so should miss
    EXPECT_FALSE(s.hit(ray_along_z(), 0.001, 2.0, rec));
}

TEST(SphereHit, HitOutsideTMinReturnsFalse) {
    sphere s(point3(0, 0, -1), 0.5);
    hit_record rec;
    // sphere surface at t≈0.5, tmin=2 so should miss
    EXPECT_FALSE(s.hit(ray_along_z(), 2.0, 1000.0, rec));
}

TEST(SphereHit, HitWithinTRangeReturnsTrue) {
    sphere s(point3(0, 0, -1), 0.5);
    hit_record rec;
    EXPECT_TRUE(s.hit(ray_along_z(), 0.001, 1000.0, rec));
    EXPECT_GT(rec.t, 0.001);
    EXPECT_LT(rec.t, 1000.0);
}

TEST(SphereHit, RecordTIsCorrect) {
    sphere s(point3(0, 0, -1), 0.5);
    hit_record rec;
    s.hit(ray_along_z(), 0.001, 1000.0, rec);
    EXPECT_NEAR(rec.t, 0.5, 1e-9); // front surface at z=-0.5, t=0.5
}

TEST(SphereHit, RecordPointIsOnSphere) {
    sphere s(point3(0, 0, -1), 0.5);
    hit_record rec;
    s.hit(ray_along_z(), 0.001, 1000.0, rec);
    double dist = (rec.p - point3(0, 0, -1)).length();
    EXPECT_NEAR(dist, 0.5, 1e-9);
}

TEST(SphereHit, OutwardNormalPointsAwayFromCentre) {
    sphere s(point3(0, 0, -1), 0.5);
    hit_record rec;
    s.hit(ray_along_z(), 0.001, 1000.0, rec);
    // Normal at front face should point toward +z (toward ray origin)
    EXPECT_NEAR(rec.normal.z(), 1.0, 1e-9);
}

TEST(SphereHit, RayFromOutsideFrontFace) {
    sphere s(point3(0, 0, -1), 0.5);
    hit_record rec;
    s.hit(ray_along_z(), 0.001, 1000.0, rec);
    EXPECT_TRUE(rec.front_face);
}

TEST(SphereHit, RayFromInsideBackFace) {
    sphere s(point3(0, 0, -1), 2.0); // large sphere, origin is inside
    hit_record rec;
    s.hit(ray_along_z(), 0.001, 1000.0, rec);
    EXPECT_FALSE(rec.front_face);
}