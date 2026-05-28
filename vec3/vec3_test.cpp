#include "vec3.h"
#include <gtest/gtest.h>
#include <stdexcept>

TEST(Vec3Test, DefaultConstruction) {
    vec3 v;
    EXPECT_DOUBLE_EQ(v.x(), 0.0);
    EXPECT_DOUBLE_EQ(v.y(), 0.0);
    EXPECT_DOUBLE_EQ(v.z(), 0.0);
}

TEST(Vec3Test, InputConstruction) {
    vec3 v(1, 2, 3);
    EXPECT_DOUBLE_EQ(v.x(), 1.0);
    EXPECT_DOUBLE_EQ(v.y(), 2.0);
    EXPECT_DOUBLE_EQ(v.z(), 3.0);
}

TEST(Vec3Test, UnaryNegation) {
    vec3 u(1, 2, 3);
    vec3 v = -u;
    EXPECT_DOUBLE_EQ(v.x(), -1.0);
    EXPECT_DOUBLE_EQ(v.y(), -2.0);
    EXPECT_DOUBLE_EQ(v.z(), -3.0);    
}

TEST(Vec3Test, SquareBracketOperator) {
    vec3 v(1, 2, 3);
    EXPECT_DOUBLE_EQ(v.x(), v[0]);
    EXPECT_DOUBLE_EQ(v.y(), v[1]);
    EXPECT_DOUBLE_EQ(v.z(), v[2]);
    EXPECT_THROW(v[-1], std::out_of_range);
    EXPECT_THROW(v[3], std::out_of_range);    
}

TEST(Vec3Test, AdditionAssignment) {
    vec3 a(1.0, 2.0, 3.0);
    vec3 b(4.0, 5.0, 6.0);
    a += b;
    EXPECT_DOUBLE_EQ(a.x(), 5.0);
    EXPECT_DOUBLE_EQ(a.y(), 7.0);
    EXPECT_DOUBLE_EQ(a.z(), 9.0);
}

TEST(Vec3Test, ScalarMultiplication) {
    vec3 v(1.0, 2.0, 3.0);
    vec3 result = 2.0 * v;
    EXPECT_DOUBLE_EQ(result.x(), 2.0);
    EXPECT_DOUBLE_EQ(result.y(), 4.0);
    EXPECT_DOUBLE_EQ(result.z(), 6.0);
}

TEST(Vec3Test, ScalarMultiplicationIsCommutative) {
    vec3 v(1.0, 2.0, 3.0);
    EXPECT_DOUBLE_EQ((2.0 * v).x(), (v * 2.0).x());
}

TEST(Vec3Test, ScalarDivision) {
    vec3 v(2.0, 4.0, 6.0);
    vec3 result = v / 2;
    EXPECT_DOUBLE_EQ(result.x(), 1.0);
    EXPECT_DOUBLE_EQ(result.y(), 2.0);
    EXPECT_DOUBLE_EQ(result.z(), 3.0);
}

// length
TEST(Vec3Test, LengthSquared) {
    vec3 v(1.0, 2.0, 3.0);
    EXPECT_DOUBLE_EQ(v.length_squared(), 14.0);
}

TEST(Vec3Test, Length) {
    vec3 v(0.0, 3.0, 4.0);
    EXPECT_DOUBLE_EQ(v.length(), 5.0);
}

// free functions
TEST(Vec3Test, DotProduct) {
    vec3 a(1.0, 2.0, 3.0);
    vec3 b(4.0, 5.0, 6.0);
    EXPECT_DOUBLE_EQ(dot(a, b), 32.0);
}

TEST(Vec3Test, CrossProduct) {
    vec3 a(1.0, 0.0, 0.0);
    vec3 b(0.0, 1.0, 0.0);
    vec3 result = cross(a, b);
    EXPECT_DOUBLE_EQ(result.x(), 0.0);
    EXPECT_DOUBLE_EQ(result.y(), 0.0);
    EXPECT_DOUBLE_EQ(result.z(), 1.0);
}

TEST(Vec3Test, UnitVector) {
    vec3 v(0.0, 3.0, 4.0);
    vec3 unit = unit_vector(v);
    EXPECT_NEAR(unit.length(), 1.0, 1e-10);
}