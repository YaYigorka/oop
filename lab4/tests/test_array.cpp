#include <gtest/gtest.h>
#include "array.hpp"
#include "point.hpp"

TEST(ArrayTest, DefaultConstructor) {
    Array<int> arr;
    EXPECT_EQ(arr.getSize(), 0);
    EXPECT_EQ(arr.getCapacity(), 1);
    EXPECT_TRUE(arr.empty());
}

TEST(ArrayTest, SizeConstructor) {
    Array<int> arr(5);
    EXPECT_EQ(arr.getSize(), 0);
    EXPECT_EQ(arr.getCapacity(), 5);
}

TEST(ArrayTest, PushBack) {
    Array<int> arr;
    arr.push_back(1);
    EXPECT_EQ(arr.getSize(), 1);
    EXPECT_EQ(arr.back(), 1);
    
    arr.push_back(2);
    EXPECT_EQ(arr.getSize(), 2);
    EXPECT_EQ(arr.back(), 2);
}

TEST(ArrayTest, PopBack) {
    Array<int> arr;
    arr.push_back(1);
    arr.push_back(2);
    arr.push_back(3);
    
    arr.pop_back();
    EXPECT_EQ(arr.getSize(), 2);
    EXPECT_EQ(arr.back(), 2);
    
    arr.pop_back();
    EXPECT_EQ(arr.getSize(), 1);
    EXPECT_EQ(arr.back(), 1);
}

TEST(ArrayTest, AccessMethods) {
    Array<int> arr;
    arr.push_back(10);
    arr.push_back(20);
    arr.push_back(30);
    
    EXPECT_EQ(arr.takeByIndex(0), 10);
    EXPECT_EQ(arr.takeByIndex(1), 20);
    EXPECT_EQ(arr.front(), 10);
    EXPECT_EQ(arr.back(), 30);
}

TEST(ArrayTest, Resize) {
    Array<int> arr;
    arr.push_back(1);
    arr.push_back(2);
    
    EXPECT_EQ(arr.getCapacity(), 2);
    arr.resize(10);
    EXPECT_EQ(arr.getCapacity(), 10);
    EXPECT_EQ(arr.getSize(), 2);
}

TEST(ArrayTest, Clear) {
    Array<int> arr;
    arr.push_back(1);
    arr.push_back(2);
    
    EXPECT_FALSE(arr.empty());
    arr.clear();
    EXPECT_TRUE(arr.empty());
    EXPECT_EQ(arr.getSize(), 0);
}

TEST(ArrayTest, WithPoints) {
    Array<Point<int>> arr;
    arr.push_back(Point<int>(1, 2));
    arr.push_back(Point<int>(3, 4));
    
    EXPECT_EQ(arr.getSize(), 2);
    EXPECT_EQ(arr.takeByIndex(0).getX(), 1);
    EXPECT_EQ(arr.takeByIndex(1).getY(), 4);
}