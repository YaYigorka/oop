#include <gtest/gtest.h>
#include <string>
#include <exception>
#include <iostream>
#include <algorithm>
#include <cstddef>

#include "DynamicArray.hpp"
#include "Eleven.hpp"
#include "MyErrors.hpp"


TEST(DynamicArrayTest, DefaultConstructor) {
    DynamicArray arr;
    EXPECT_EQ(arr.getSize(), 0);
    EXPECT_GE(arr.getCapacity(), 10);
    EXPECT_TRUE(arr.empty());
}

TEST(DynamicArrayTest, CapacityConstructor) {
    DynamicArray arr(20);
    EXPECT_EQ(arr.getSize(), 0);
    EXPECT_EQ(arr.getCapacity(), 20);
    EXPECT_TRUE(arr.empty());
}

TEST(DynamicArrayTest, StringConstructor) {
    DynamicArray arr("123");
    EXPECT_EQ(arr.getSize(), 3);
    EXPECT_EQ(arr.takeByIndex(0), 3);
    EXPECT_EQ(arr.takeByIndex(1), 2);
    EXPECT_EQ(arr.takeByIndex(2), 1);
}

TEST(DynamicArrayTest, StringConstructorWithA) {
    DynamicArray arr("1A3");
    EXPECT_EQ(arr.getSize(), 3);
    EXPECT_EQ(arr.takeByIndex(0), 3);
    EXPECT_EQ(arr.takeByIndex(1), 10);
    EXPECT_EQ(arr.takeByIndex(2), 1);
}

TEST(DynamicArrayTest, CopyConstructor) {
    DynamicArray arr1("123");
    DynamicArray arr2(arr1);
    
    EXPECT_EQ(arr1.getSize(), arr2.getSize());
    for (size_t i = 0; i < arr1.getSize(); ++i) {
        EXPECT_EQ(arr1.takeByIndex(i), arr2.takeByIndex(i));
    }
}


TEST(DynamicArrayTest, PushBack) {
    DynamicArray arr;
    arr.push_back(5);
    arr.push_back(10);
    
    EXPECT_EQ(arr.getSize(), 2);
    EXPECT_EQ(arr.takeByIndex(0), 5);
    EXPECT_EQ(arr.takeByIndex(1), 10);
}

TEST(DynamicArrayTest, PopBack) {
    DynamicArray arr("123");
    size_t originalSize = arr.getSize();
    
    arr.pop_back();
    EXPECT_EQ(arr.getSize(), originalSize - 1);
}

TEST(DynamicArrayTest, FrontBack) {
    DynamicArray arr("123");
    EXPECT_EQ(arr.front(), 3);
    EXPECT_EQ(arr.back(), 1);
}

TEST(DynamicArrayTest, FrontBackEmpty) {
    DynamicArray arr;
    EXPECT_THROW(arr.front(), std::out_of_range);
    EXPECT_THROW(arr.back(), std::out_of_range);
}

TEST(DynamicArrayTest, Clear) {
    DynamicArray arr("123");
    arr.clear();
    
    EXPECT_EQ(arr.getSize(), 0);
    EXPECT_TRUE(arr.empty());
}

TEST(DynamicArrayTest, IndexOperator) {
    DynamicArray arr("123");
    EXPECT_EQ(arr.takeByIndex(0), 3);
    EXPECT_EQ(arr.takeByIndex(1), 2);
    EXPECT_EQ(arr.takeByIndex(2), 1);
}

TEST(DynamicArrayTest, IndexOperatorOutOfRange) {
    DynamicArray arr("123");
    EXPECT_THROW(arr.takeByIndex(5), std::out_of_range);
}

TEST(DynamicArrayTest, ConstIndexOperator) {
    const DynamicArray arr("123");
    EXPECT_EQ(arr.takeByIndex(0), 3);
    EXPECT_EQ(arr.takeByIndex(1), 2);
    EXPECT_EQ(arr.takeByIndex(2), 1);
}

TEST(DynamicArrayTest, UpSizeDownSize) {
    DynamicArray arr;
    arr.upSize();
    EXPECT_EQ(arr.getSize(), 1);
    arr.downSize();
    EXPECT_EQ(arr.getSize(), 0);
}

TEST(ElevenTest, DefaultConstructor) {
    Eleven num;
    EXPECT_EQ(num.decRead(), 0);
    EXPECT_TRUE(num.get_array_link().empty());
    EXPECT_EQ(num.getNumber(), "");
}

TEST(ElevenTest, StringConstructor) {
    Eleven num("123", 456);
    EXPECT_EQ(num.decRead(), 456);
    EXPECT_EQ(num.getNumber(), "123");
}

TEST(ElevenTest, StringConstructorWithA) {
    Eleven num("1A3", 100);
    EXPECT_EQ(num.decRead(), 100);
    EXPECT_EQ(num.getNumber(), "1A3");
}

TEST(ElevenTest, CopyConstructor) {
    Eleven num1("123", 456);
    Eleven num2(num1);
    
    EXPECT_EQ(num1.decRead(), num2.decRead());
    EXPECT_EQ(num1.getNumber(), num2.getNumber());
}


TEST(ElevenTest, Write) {
    Eleven num;
    num.write("456", 789);
    
    EXPECT_EQ(num.decRead(), 789);
    EXPECT_EQ(num.getNumber(), "456");
}

TEST(ElevenTest, Erase) {
    Eleven num("123", 456);
    num.erase();
    
    EXPECT_EQ(num.decRead(), 456);
    EXPECT_TRUE(num.get_array_link().empty());
    EXPECT_EQ(num.getNumber(), "");
}

TEST(ElevenTest, AdditionBasic) {
    Eleven num1("123", 0);
    Eleven num2("456", 0);
    Eleven result(add(num1, num2));
    
    EXPECT_EQ(result.getNumber(), "579");
}

TEST(ElevenTest, AdditionWithCarry) {
    Eleven num1("A", 0);
    Eleven num2("1", 0);
    Eleven result(add(num1, num2));
    
    EXPECT_EQ(result.getNumber(), "10");
}

TEST(ElevenTest, SubtractionBasic) {
    Eleven num1("456", 0);
    Eleven num2("123", 0);
    Eleven result(sub(num1, num2));
    
    EXPECT_EQ(result.getNumber(), "333");
}

TEST(ElevenTest, SubtractionWithBorrow) {
    Eleven num1("100", 0);
    Eleven num2("1", 0);
    Eleven result(sub(num1, num2));
    
    EXPECT_EQ(result.getNumber(), "AA");
}

TEST(ElevenTest, ComparisonLessThan) {
    Eleven num1("123", 0);
    Eleven num2("456", 0);
    
    EXPECT_TRUE(less(num1, num2));
    EXPECT_FALSE(less(num2, num1));
}

TEST(ElevenTest, ComparisonGreaterThan) {
    Eleven num1("456", 0);
    Eleven num2("123", 0);
    
    EXPECT_TRUE(more(num1, num2));
    EXPECT_FALSE(more(num2, num1));
}

TEST(ElevenTest, ComparisonEqual) {
    Eleven num1("123", 0);
    Eleven num2("123", 0);
    
    EXPECT_TRUE(equal(num1, num2));
}

TEST(ElevenTest, ComparisonNotEqual) {
    Eleven num1("123", 0);
    Eleven num2("456", 0);
    
    EXPECT_FALSE(equal(num1, num2));
}

TEST(ElevenTest, ComparisonDifferentLengths) {
    Eleven num1("123", 0);
    Eleven num2("1234", 0);
    
    EXPECT_TRUE(less(num1, num2));
    EXPECT_TRUE(more(num2, num1));
    EXPECT_FALSE(equal(num1, num2));
}

TEST(ElevenTest, GetNumberEmpty) {
    Eleven num;
    EXPECT_EQ(num.getNumber(), "");
}

TEST(ElevenTest, ComplexAddition) {
    Eleven num1("A", 0);
    Eleven num2("A", 0);
    Eleven result(add(num1, num2));
    
    EXPECT_EQ(result.getNumber(), "19");
}

TEST(MyErrorsTest, NegativeValueErrorDefault) {
    NegetiveValueError error;
    EXPECT_STREQ(error.what(), "Negative value error");
}

TEST(MyErrorsTest, NegativeValueErrorWithContext) {
    NegetiveValueError error("subtraction result");
    EXPECT_STREQ(error.what(), "Negative value error:subtraction result");
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}