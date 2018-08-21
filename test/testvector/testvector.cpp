#include <Vector3f.h>
#include "gtest/gtest.h"

bool compareWithPrecision(float A, float B, float epsilon = 0.001f)
{
    return (fabs(A - B) < epsilon);
}

TEST(VectorTest, addTwoVectors) {
    Vector3f myVector(1,1,1);
    Vector3f otherVector(1,2,3);

    Vector3f result = myVector.add(otherVector);

    EXPECT_EQ(result.x, 2);
    EXPECT_EQ(result.y, 3);
    EXPECT_EQ(result.z, 4);
}

TEST(VectorTest, addTwoVectorsOperator) {
    Vector3f myVector(1,1,1);
    Vector3f otherVector(1,2,3);

    Vector3f result = myVector + otherVector;

    EXPECT_EQ(result.x, 2);
    EXPECT_EQ(result.y, 3);
    EXPECT_EQ(result.z, 4);
}

TEST(VectorTest, subtractTwoVectors) {
    Vector3f myVector(1,1,1);
    Vector3f otherVector(1,2,3);

    Vector3f result = myVector.substract(otherVector);

    EXPECT_EQ(result.x, 0);
    EXPECT_EQ(result.y, -1);
    EXPECT_EQ(result.z, -2);
}

TEST(VectorTest, subtractTwoVectorsOperator) {
    Vector3f myVector(1,1,1);
    Vector3f otherVector(1,2,3);

    Vector3f result = myVector - otherVector;

    EXPECT_EQ(result.x, 0);
    EXPECT_EQ(result.y, -1);
    EXPECT_EQ(result.z, -2);
}

TEST(VectorTest, length){
    Vector3f myVector(-5, -6, -8);

    ASSERT_TRUE(compareWithPrecision(myVector.length(), 11.18033f));
}

TEST(VectorTest, multiplyScalar){
    Vector3f myVector(5, 6, 8);
    Vector3f result = myVector.multiplyScalar(5);

    EXPECT_EQ(result.x,25);
    EXPECT_EQ(result.y,30);
    EXPECT_EQ(result.z,40);
}

TEST(VectorTest, multiplyScalarOperator){
    Vector3f myVector(5, 6, 8);
    Vector3f result = myVector * 5;

    EXPECT_EQ(result.x,25);
    EXPECT_EQ(result.y,30);
    EXPECT_EQ(result.z,40);
}

TEST(VectorTest, normalize){
    Vector3f myVector(5, 6, 8);
    Vector3f result = myVector.normalize();

    ASSERT_TRUE(compareWithPrecision(result.x, 0.44721f));
    ASSERT_TRUE(compareWithPrecision(result.y, 0.5366f));
    ASSERT_TRUE(compareWithPrecision(result.z, 0.71554f));
}

TEST(VectorTest, invert){
    Vector3f myVector(5, 6, 8);
    Vector3f result = myVector.invert();

    EXPECT_EQ(result.x, myVector.x*-1);
    EXPECT_EQ(result.y, myVector.y*-1);
    EXPECT_EQ(result.z, myVector.z*-1);
}



TEST(VectorTest, crossProduct) {
    Vector3f myVector(1,2,3);
    Vector3f otherVector(1, 5, 7);
    Vector3f result = myVector.crossProduct(otherVector);

    EXPECT_EQ(result.x, -1);
    EXPECT_EQ(result.y, -4);
    EXPECT_EQ(result.z, 3);
}

TEST(VectorTest, crossProductOperator) {
    Vector3f myVector(1,2,3);
    Vector3f otherVector(1, 5, 7);
    Vector3f result = myVector * otherVector;

    EXPECT_EQ(result.x, -1);
    EXPECT_EQ(result.y, -4);
    EXPECT_EQ(result.z, 3);
}

TEST(VectorTest, operatorEqual) {
    Vector3f myVector(1,2,3);
    Vector3f otherVector(1, 2, 3);
    Vector3f anotherVector(0, 0, 0);

    ASSERT_TRUE(myVector == otherVector);
    ASSERT_FALSE(myVector == anotherVector);
}

TEST(VectorTest, operatorNotEqual) {
    Vector3f myVector(1,2,3);
    Vector3f otherVector(1, 2, 3);
    Vector3f anotherVector(0, 0, 0);

    ASSERT_FALSE(myVector != otherVector);
    ASSERT_TRUE(myVector != anotherVector);
}