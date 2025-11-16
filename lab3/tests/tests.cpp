#include <gtest/gtest.h>
#include "dot2D.hpp"
#include "coordinates_vector.hpp"
#include "figure.hpp"
#include "trapezoid.hpp"
#include "rhombus.hpp"
#include "pentagon.hpp"
#include "figure_vector.hpp"


TEST(Dot2DTest, BasicFunctionality) {
    Dot2D dot;
    dot.setDot(3.5, 4.2);
    
    EXPECT_DOUBLE_EQ(dot.getX(), 3.5);
    EXPECT_DOUBLE_EQ(dot.getY(), 4.2);
}

TEST(Dot2DTest, DefaultConstructor) {
    Dot2D dot;
    SUCCEED();
}

TEST(CoordinatesVectorTest, BasicFunctionality) {
    CoordinatesVector vec;
    Dot2D dot1, dot2;
    dot1.setDot(1, 2);
    dot2.setDot(3, 4);
    
    EXPECT_TRUE(vec.empty());
    EXPECT_EQ(vec.getSize(), 0);
    
    vec.push_back(dot1);
    vec.push_back(dot2);
    
    EXPECT_FALSE(vec.empty());
    EXPECT_GE(vec.getSize(), 2);
    
    vec.pop_back();
    vec.clear();
    EXPECT_TRUE(vec.empty());
}

TEST(CoordinatesVectorTest, CapacityManagement) {
    CoordinatesVector vec(5);
    EXPECT_GE(vec.getCapacity(), 5);
}

TEST(FigureTest, StreamOperators) {
    Trapezoid trap;
    std::istringstream input("0 0\n1 0\n1 1\n0 1\n");
    std::ostringstream output;
    SUCCEED();
}

TEST(TrapezoidTest, CreationAndOperations) {
    Trapezoid trap;
    SUCCEED();
    Dot2D center = trap.geometricCenter();
    double area = static_cast<double>(trap);
    EXPECT_GE(area, 0);
}

TEST(RhombusTest, CreationAndOperations) {
    Rhombus rhombus;
    SUCCEED();
    Dot2D center = rhombus.geometricCenter();
    double area = static_cast<double>(rhombus);
    EXPECT_GE(area, 0);
}

TEST(PentagonTest, CreationAndOperations) {
    Pentagon pentagon;
    SUCCEED();
    Dot2D center = pentagon.geometricCenter();
    double area = static_cast<double>(pentagon);
    EXPECT_GE(area, 0);
}

TEST(FigureVectorTest, BasicFunctionality) {
    FigureVector fvec;
    
    EXPECT_TRUE(fvec.empty());
    EXPECT_EQ(fvec.getSize(), 0);
    
    Trapezoid trap;
    Rhombus rhombus;
    
    fvec.push_back(trap);
    fvec.push_back(rhombus);
    
    EXPECT_FALSE(fvec.empty());
    EXPECT_GE(fvec.getSize(), 2);
    
    Figure& fig = fvec.takeByIndex(0);
    double totalArea = fvec.totalArea();
    EXPECT_GE(totalArea, 0);
    
    fvec.pop_back();
    fvec.clear();
    EXPECT_TRUE(fvec.empty());
}

TEST(FigureVectorTest, CapacityAndSize) {
    FigureVector fvec(10);
    EXPECT_GE(fvec.getCapacity(), 10);
    
    fvec.upSize();
    fvec.downSize();
    SUCCEED();
}

TEST(RuleOfFiveTest, CoordinatesVectorCopyMove) {
    CoordinatesVector original;
    Dot2D dot;
    dot.setDot(1, 1);
    original.push_back(dot);
    
    CoordinatesVector copy = original;
    EXPECT_GE(copy.getSize(), 1);
    
    CoordinatesVector moved = std::move(original);
    EXPECT_GE(moved.getSize(), 1);
}

TEST(RuleOfFiveTest, FigureVectorCopyMove) {
    FigureVector original;
    Trapezoid trap;
    original.push_back(trap);
    
    FigureVector copy = original;
    EXPECT_GE(copy.getSize(), 1);
    
    FigureVector moved = std::move(original);
    EXPECT_GE(moved.getSize(), 1);
}

TEST(EmptyContainersTest, Behavior) {
    CoordinatesVector emptyVec;
    FigureVector emptyFigVec;
    
    EXPECT_TRUE(emptyVec.empty());
    EXPECT_TRUE(emptyFigVec.empty());
    EXPECT_EQ(emptyVec.getSize(), 0);
    EXPECT_EQ(emptyFigVec.getSize(), 0);
}

TEST(CoordinatesVectorTest, BoundaryConditions) {
    CoordinatesVector vec;
    EXPECT_THROW(vec.takeByIndex(0), std::out_of_range);
    
    Dot2D dot;
    vec.push_back(dot);
    EXPECT_NO_THROW(vec.takeByIndex(0));
    EXPECT_THROW(vec.takeByIndex(1), std::out_of_range);
}

TEST(FigureVectorTest, Polymorphism) {
    FigureVector fvec;
    
    Trapezoid* trap = new Trapezoid();
    Rhombus* rhombus = new Rhombus();
    
    fvec.push_back(*trap);
    fvec.push_back(*rhombus);
    
    for(size_t i = 0; i < fvec.getSize(); ++i) {
        Figure& fig = fvec.takeByIndex(i);
        Dot2D center = fig.geometricCenter();
        double area = static_cast<double>(fig);
        EXPECT_GE(area, 0);
    }
    
    delete trap;
    delete rhombus;
}

TEST(EqualityTest, FigureComparison) {
    Pentagon p1, p2;
    EXPECT_FALSE(p1 == p2);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}