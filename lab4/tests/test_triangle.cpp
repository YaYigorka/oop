#include <gtest/gtest.h>
#include <sstream>
#include "triangle.hpp"

TEST(TriangleTest, DefaultConstructor) {
    Triangle<int> t;
    EXPECT_EQ(t.geometricCenter().getX(), 0);
    EXPECT_EQ(t.geometricCenter().getY(), 0);
    EXPECT_DOUBLE_EQ(static_cast<double>(t), 0.0);
}

TEST(TriangleTest, StreamOperators) {
    Triangle<int> t;
    std::istringstream iss("0 0 3 0 0 4");
    iss >> t;
    
    EXPECT_EQ(t.geometricCenter().getX(), 1);
    EXPECT_EQ(t.geometricCenter().getY(), 1);
    
    std::ostringstream oss;
    oss << t;
    EXPECT_NE(oss.str().find("Triangle"), std::string::npos);
}

TEST(TriangleTest, GeometricCenter) {
    Triangle<int> t;
    std::istringstream iss("0 0 3 0 0 4");
    iss >> t;
    
    Point<int> center = t.geometricCenter();
    EXPECT_EQ(center.getX(), 1);
    EXPECT_EQ(center.getY(), 1);
}

TEST(TriangleTest, AreaCalculation) {
    Triangle<int> t;
    std::istringstream iss("0 0 3 0 0 4");
    iss >> t;
    
    double area = static_cast<double>(t);
    EXPECT_NEAR(area, 6.0, 0.001);
}

TEST(TriangleTest, Comparison) {
    Triangle<int> t1, t2, t3;
    std::istringstream iss1("0 0 3 0 0 4");
    std::istringstream iss2("0 0 3 0 0 4");
    std::istringstream iss3("1 1 4 1 1 5");
    
    iss1 >> t1;
    iss2 >> t2;
    iss3 >> t3;
    
    EXPECT_TRUE(t1 == t2);
    EXPECT_FALSE(t1 == t3);
    EXPECT_TRUE(t1 != t3);
}

TEST(TriangleTest, DifferentTypes) {
    Triangle<double> t;
    std::istringstream iss("0 0 3 0 0 4");
    iss >> t;
    
    EXPECT_NEAR(static_cast<double>(t), 6.0, 0.001);
}