#include <Color.h>
#include "gtest/gtest.h"

bool compareWithPrecision(float A, float B, float epsilon = 0.001f)
{
    return (fabs(A - B) < epsilon);
}

TEST(ColorTest, createColorDefault) {
    Color myColor;
    EXPECT_EQ(myColor.r, 0);
    EXPECT_EQ(myColor.g, 0);
    EXPECT_EQ(myColor.b, 0);
}

TEST(ColorTest, createColor) {
    Color myColor(1,2,3);
    EXPECT_EQ(myColor.r, 1);
    EXPECT_EQ(myColor.g, 2);
    EXPECT_EQ(myColor.b, 3);
}

TEST(ColorTest, operatorAdd) {
    Color myColor(1,2,3);
    Color otherColor(4,5,6);

    Color result = myColor + otherColor;

    EXPECT_EQ(result.r, 5);
    EXPECT_EQ(result.g, 7);
    EXPECT_EQ(result.b, 9);
}

TEST(ColorTest, operatorSubstract) {
    Color myColor(1,2,3);
    Color otherColor(4,5,6);

    Color result = myColor - otherColor;

    EXPECT_EQ(result.r, -3);
    EXPECT_EQ(result.g, -3);
    EXPECT_EQ(result.b, -3);
}

TEST(ColorTest, operatorMultiplyColor) {
    Color myColor(1,2,3);
    Color otherColor(4,5,6);

    Color result = myColor * otherColor;

    EXPECT_EQ(result.r, 4);
    EXPECT_EQ(result.g, 10);
    EXPECT_EQ(result.b, 18);
}

TEST(ColorTest, operatorMultiplyScalar) {
    Color myColor(1,2,3);

    Color result = myColor * 2;

    EXPECT_EQ(result.r,  2);
    EXPECT_EQ(result.g,  4);
    EXPECT_EQ(result.b,  6);
}

TEST(ColorTest, clamp) {
    Color myColor(2,3,4);

    Color result = myColor.clamp();

    EXPECT_EQ(result.r, 1);
    EXPECT_EQ(result.g, 1);
    EXPECT_EQ(result.b, 1);
}

TEST(ColorTest, getRgbValuesClamped) {
    Color myColor(2,3,4);

    std::tuple<int, int, int> values = myColor.getRgbValues();

    EXPECT_EQ(std::get<0>(values), 255);
    EXPECT_EQ(std::get<1>(values), 255);
    EXPECT_EQ(std::get<2>(values), 255);
}

TEST(ColorTest, getRgbValues) {
    Color myColor(0.1f,0.2f, 0.3f);

    std::tuple<int, int, int> values = myColor.getRgbValues();

    EXPECT_EQ(std::get<0>(values) , 25);
    EXPECT_EQ(std::get<1>(values) , 51);
    EXPECT_EQ(std::get<2>(values) , 76);
}
