#include <gtest/gtest.h>
#include "hittable_list.h"
#include "hittable/sphere/sphere.h"

ray ray_along_neg_z() {
    return ray(point3(0, 0, 0), vec3(0, 0, -1));
}

std::shared_ptr<hittable> make_sphere(point3 centre, double radius) {
    return std::make_shared<sphere>(centre, radius);
}

TEST(HittableListConstruction, DefaultConstructedListHitsNothing) {
    hittable_list list;
    hit_record rec;
    EXPECT_FALSE(list.hit(ray_along_neg_z(), 0.001, 1000.0, rec));
}

TEST(HittableListConstruction, SingleObjectConstructorRegistersObject) {
    hittable_list list(make_sphere(point3(0, 0, -1), 0.5));
    hit_record rec;
    EXPECT_TRUE(list.hit(ray_along_neg_z(), 0.001, 1000.0, rec));
}

TEST(HittableListClear, ClearedListHitsNothing) {
    hittable_list list;
    list.add(make_sphere(point3(0, 0, -1), 0.5));
    list.clear();
    hit_record rec;
    EXPECT_FALSE(list.hit(ray_along_neg_z(), 0.001, 1000.0, rec));
}

TEST(HittableListHit, EmptyListReturnsFalse) {
    hittable_list list;
    hit_record rec;
    EXPECT_FALSE(list.hit(ray_along_neg_z(), 0.001, 1000.0, rec));
}

TEST(HittableListHit, SingleSphereHit) {
    hittable_list list;
    list.add(make_sphere(point3(0, 0, -1), 0.5));
    hit_record rec;
    EXPECT_TRUE(list.hit(ray_along_neg_z(), 0.001, 1000.0, rec));
}

TEST(HittableListHit, SingleSphereMiss) {
    hittable_list list;
    list.add(make_sphere(point3(5, 5, -1), 0.5)); // off to the side
    hit_record rec;
    EXPECT_FALSE(list.hit(ray_along_neg_z(), 0.001, 1000.0, rec));
}

TEST(HittableListHit, AllObjectsMissReturnsFalse) {
    hittable_list list;
    list.add(make_sphere(point3(5, 0, -1), 0.5));
    list.add(make_sphere(point3(0, 5, -1), 0.5));
    hit_record rec;
    EXPECT_FALSE(list.hit(ray_along_neg_z(), 0.001, 1000.0, rec));
}

TEST(HittableListHit, ReturnsClosestOfTwoSpheres) {
    hittable_list list;
    list.add(make_sphere(point3(0, 0, -3), 0.5)); // far, front surface t≈2.5
    list.add(make_sphere(point3(0, 0, -1), 0.5)); // near, front surface t≈0.5
    hit_record rec;
    EXPECT_TRUE(list.hit(ray_along_neg_z(), 0.001, 1000.0, rec));
    EXPECT_NEAR(rec.t, 0.5, 1e-9);
}

TEST(HittableListHit, ClosestReturnedRegardlessOfInsertionOrder) {
    hittable_list list;
    list.add(make_sphere(point3(0, 0, -1), 0.5)); // near, inserted first
    list.add(make_sphere(point3(0, 0, -3), 0.5)); // far, inserted second
    hit_record rec;
    EXPECT_TRUE(list.hit(ray_along_neg_z(), 0.001, 1000.0, rec));
    EXPECT_NEAR(rec.t, 0.5, 1e-9);
}

TEST(HittableListHit, RecordPointIsOnClosestSphere) {
    hittable_list list;
    list.add(make_sphere(point3(0, 0, -1), 0.5));
    list.add(make_sphere(point3(0, 0, -3), 0.5));
    hit_record rec;
    list.hit(ray_along_neg_z(), 0.001, 1000.0, rec);
    // Hit point should be on near sphere surface
    double dist = (rec.p - point3(0, 0, -1)).length();
    EXPECT_NEAR(dist, 0.5, 1e-9);
}

TEST(HittableListHit, ObjectBeyondTMaxNotHit) {
    hittable_list list;
    list.add(make_sphere(point3(0, 0, -5), 0.5)); // front surface at t≈4.5
    hit_record rec;
    EXPECT_FALSE(list.hit(ray_along_neg_z(), 0.001, 2.0, rec));
}

TEST(HittableListHit, ObjectBeforeTMinNotHit) {
    hittable_list list;
    list.add(make_sphere(point3(0, 0, -1), 0.5)); // front surface at t≈0.5
    hit_record rec;
    EXPECT_FALSE(list.hit(ray_along_neg_z(), 2.0, 1000.0, rec));
}

TEST(HittableListHit, OnlyObjectWithinTRangeReturned) {
    hittable_list list;
    list.add(make_sphere(point3(0, 0, -1), 0.5));  // t≈0.5, within range
    list.add(make_sphere(point3(0, 0, -10), 0.5)); // t≈9.5, beyond tmax
    hit_record rec;
    EXPECT_TRUE(list.hit(ray_along_neg_z(), 0.001, 5.0, rec));
    EXPECT_NEAR(rec.t, 0.5, 1e-9);
}