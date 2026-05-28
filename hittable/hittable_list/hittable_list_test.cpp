#include <gtest/gtest.h>
#include "hittable_list.h"
#include "hittable/sphere/sphere.h"
#include "interval/interval.h"

ray ray_along_neg_z() {
    return ray(point3(0, 0, 0), vec3(0, 0, -1));
}

std::shared_ptr<hittable> make_sphere(point3 centre, double radius) {
    return std::make_shared<sphere>(centre, radius);
}

const interval default_interval(0.001, 1000.0);

TEST(HittableListConstruction, DefaultConstructedListHitsNothing) {
    hittable_list list;
    hit_record rec;
    EXPECT_FALSE(list.hit(ray_along_neg_z(), default_interval, rec));
}

TEST(HittableListConstruction, SingleObjectConstructorRegistersObject) {
    hittable_list list(make_sphere(point3(0, 0, -1), 0.5));
    hit_record rec;
    EXPECT_TRUE(list.hit(ray_along_neg_z(), default_interval, rec));
}

TEST(HittableListClear, ClearedListHitsNothing) {
    hittable_list list;
    list.add(make_sphere(point3(0, 0, -1), 0.5));
    list.clear();
    hit_record rec;
    EXPECT_FALSE(list.hit(ray_along_neg_z(), default_interval, rec));
}

TEST(HittableListHit, EmptyListReturnsFalse) {
    hittable_list list;
    hit_record rec;
    EXPECT_FALSE(list.hit(ray_along_neg_z(), default_interval, rec));
}

TEST(HittableListHit, SingleSphereHit) {
    hittable_list list;
    list.add(make_sphere(point3(0, 0, -1), 0.5));
    hit_record rec;
    EXPECT_TRUE(list.hit(ray_along_neg_z(), default_interval, rec));
}

TEST(HittableListHit, SingleSphereMiss) {
    hittable_list list;
    list.add(make_sphere(point3(5, 5, -1), 0.5));
    hit_record rec;
    EXPECT_FALSE(list.hit(ray_along_neg_z(), default_interval, rec));
}

TEST(HittableListHit, AllObjectsMissReturnsFalse) {
    hittable_list list;
    list.add(make_sphere(point3(5, 0, -1), 0.5));
    list.add(make_sphere(point3(0, 5, -1), 0.5));
    hit_record rec;
    EXPECT_FALSE(list.hit(ray_along_neg_z(), default_interval, rec));
}

TEST(HittableListHit, ReturnsClosestOfTwoSpheres) {
    hittable_list list;
    list.add(make_sphere(point3(0, 0, -3), 0.5));
    list.add(make_sphere(point3(0, 0, -1), 0.5));
    hit_record rec;
    EXPECT_TRUE(list.hit(ray_along_neg_z(), default_interval, rec));
    EXPECT_NEAR(rec.t, 0.5, 1e-9);
}

TEST(HittableListHit, ClosestReturnedRegardlessOfInsertionOrder) {
    hittable_list list;
    list.add(make_sphere(point3(0, 0, -1), 0.5));
    list.add(make_sphere(point3(0, 0, -3), 0.5));
    hit_record rec;
    EXPECT_TRUE(list.hit(ray_along_neg_z(), default_interval, rec));
    EXPECT_NEAR(rec.t, 0.5, 1e-9);
}

TEST(HittableListHit, RecordPointIsOnClosestSphere) {
    hittable_list list;
    list.add(make_sphere(point3(0, 0, -1), 0.5));
    list.add(make_sphere(point3(0, 0, -3), 0.5));
    hit_record rec;
    list.hit(ray_along_neg_z(), default_interval, rec);
    double dist = (rec.p - point3(0, 0, -1)).length();
    EXPECT_NEAR(dist, 0.5, 1e-9);
}

TEST(HittableListHit, ObjectBeyondTMaxNotHit) {
    hittable_list list;
    list.add(make_sphere(point3(0, 0, -5), 0.5));
    hit_record rec;
    EXPECT_FALSE(list.hit(ray_along_neg_z(), interval(0.001, 2.0), rec));
}

TEST(HittableListHit, ObjectBeforeTMinNotHit) {
    hittable_list list;
    list.add(make_sphere(point3(0, 0, -1), 0.5));
    hit_record rec;
    EXPECT_FALSE(list.hit(ray_along_neg_z(), interval(2.0, 1000.0), rec));
}

TEST(HittableListHit, OnlyObjectWithinTRangeReturned) {
    hittable_list list;
    list.add(make_sphere(point3(0, 0, -1), 0.5));
    list.add(make_sphere(point3(0, 0, -10), 0.5));
    hit_record rec;
    EXPECT_TRUE(list.hit(ray_along_neg_z(), interval(0.001, 5.0), rec));
    EXPECT_NEAR(rec.t, 0.5, 1e-9);
}