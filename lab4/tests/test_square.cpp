#include <gtest/gtest.h>
#include <sstream>
#include "square.hpp"

TEST(SquareTest, DefaultConstructor) {
    Square<int> s;
    EXPECT_EQ(s.geometricCenter().getX(), 0);
    EXPECT_EQ(s.geometricCenter().getY(), 0);
    EXPECT_DOUBLE_EQ(static_cast<double>(s), 0.0);
}

TEST(SquareTest, StreamOperators) {
    Square<int> s;
    std::istringstream iss("0 0 2 0 2 2 0 2");
    iss >> s;
    
    EXPECT_EQ(s.geometricCenter().getX(), 1);
    EXPECT_EQ(s.geometricCenter().getY(), 1);
    
    std::ostringstream oss;
    oss << s;
    EXPECT_NE(oss.str().find("Square"), std::string::npos);
}

TEST(SquareTest, GeometricCenter) {
    Square<int> s;
    std::istringstream iss("0 0 2 0 2 2 0 2");
    iss >> s;
    
    Point<int> center = s.geometricCenter();
    EXPECT_EQ(center.getX(), 1);
    EXPECT_EQ(center.getY(), 1);
}

TEST(SquareTest, AreaCalculation) {
    Square<int> s;
    std::istringstream iss("0 0 2 0 2 2 0 2");
    iss >> s;
    
    double area = static_cast<double>(s);
    EXPECT_NEAR(area, 4.0, 0.001);
}

TEST(SquareTest, Comparison) {
    Square<int> s1, s2, s3;
    std::istringstream iss1("0 0 2 0 2 2 0 2");
    std::istringstream iss2("0 0 2 0 2 2 0 2");
    std::istringstream iss3("1 1 3 1 3 3 1 3");
    
    iss1 >> s1;
    iss2 >> s2;
    iss3 >> s3;
    
    EXPECT_TRUE(s1 == s2);
    EXPECT_FALSE(s1 == s3);
    EXPECT_TRUE(s1 != s3);
}

TEST(SquareTest, LargeSquare) {
    Square<int> s;
    std::istringstream iss("0 0 10 0 10 10 0 10");
    iss >> s;
    
    EXPECT_NEAR(static_cast<double>(s), 100.0, 0.001);
}