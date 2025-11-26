#include <gtest/gtest.h>
#include <sstream>
#include "point.hpp"

TEST(PointTest, DefaultConstructor) {
    Point<int> p;
    EXPECT_EQ(p.getX(), 0);
    EXPECT_EQ(p.getY(), 0);
}

TEST(PointTest, ParameterizedConstructor) {
    Point<int> p(3, 4);
    EXPECT_EQ(p.getX(), 3);
    EXPECT_EQ(p.getY(), 4);
}

TEST(PointTest, SetPoint) {
    Point<int> p;
    p.setPoint(5, 10);
    EXPECT_EQ(p.getX(), 5);
    EXPECT_EQ(p.getY(), 10);
}

TEST(PointTest, ComparisonOperators) {
    Point<int> p1(1, 2);
    Point<int> p2(1, 2);
    Point<int> p3(3, 4);
    
    EXPECT_TRUE(p1 == p2);
    EXPECT_FALSE(p1 == p3);
    EXPECT_TRUE(p1 != p3);
    EXPECT_FALSE(p1 != p2);
}

TEST(PointTest, StreamOperators) {
    Point<int> p(7, 8);
    
    std::ostringstream oss;
    oss << p;
    EXPECT_NE(oss.str().find("(7, 8)"), std::string::npos);
    
    Point<int> p2;
    std::istringstream iss("12 15");
    iss >> p2;
    EXPECT_EQ(p2.getX(), 12);
    EXPECT_EQ(p2.getY(), 15);
}

TEST(PointTest, DifferentTypes) {
    Point<double> p(1.5, 2.7);
    EXPECT_DOUBLE_EQ(p.getX(), 1.5);
    EXPECT_DOUBLE_EQ(p.getY(), 2.7);
}