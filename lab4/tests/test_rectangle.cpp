#include <gtest/gtest.h>
#include <sstream>
#include "rectangle.hpp"

TEST(RectangleTest, DefaultConstructor) {
    Rectangle<int> r;
    EXPECT_EQ(r.geometricCenter().getX(), 0);
    EXPECT_EQ(r.geometricCenter().getY(), 0);
    EXPECT_DOUBLE_EQ(static_cast<double>(r), 0.0);
}

TEST(RectangleTest, StreamOperators) {
    Rectangle<int> r;
    std::istringstream iss("0 0 4 0 4 2 0 2");
    iss >> r;
    
    EXPECT_EQ(r.geometricCenter().getX(), 2);
    EXPECT_EQ(r.geometricCenter().getY(), 1);
    
    std::ostringstream oss;
    oss << r;
    EXPECT_NE(oss.str().find("Rectangle"), std::string::npos);
}

TEST(RectangleTest, GeometricCenter) {
    Rectangle<int> r;
    std::istringstream iss("0 0 4 0 4 2 0 2");
    iss >> r;
    
    Point<int> center = r.geometricCenter();
    EXPECT_EQ(center.getX(), 2);
    EXPECT_EQ(center.getY(), 1);
}

TEST(RectangleTest, AreaCalculation) {
    Rectangle<int> r;
    std::istringstream iss("0 0 4 0 4 2 0 2");
    iss >> r;
    
    double area = static_cast<double>(r);
    EXPECT_NEAR(area, 8.0, 0.001);
}

TEST(RectangleTest, NonSquareRectangle) {
    Rectangle<int> r;
    std::istringstream iss("0 0 6 0 6 3 0 3");
    iss >> r;
    
    EXPECT_NEAR(static_cast<double>(r), 18.0, 0.001);
}

TEST(RectangleTest, Comparison) {
    Rectangle<int> r1, r2, r3;
    std::istringstream iss1("0 0 4 0 4 2 0 2");
    std::istringstream iss2("0 0 4 0 4 2 0 2");
    std::istringstream iss3("1 1 5 1 5 3 1 3");
    
    iss1 >> r1;
    iss2 >> r2;
    iss3 >> r3;
    
    EXPECT_TRUE(r1 == r2);
    EXPECT_FALSE(r1 == r3);
    EXPECT_TRUE(r1 != r3);
}

TEST(RectangleTest, DifferentTypes) {
    Rectangle<double> r;
    std::istringstream iss("0 0 2.5 0 2.5 1.5 0 1.5");
    iss >> r;
    
    EXPECT_NEAR(static_cast<double>(r), 3.75, 0.001);
}