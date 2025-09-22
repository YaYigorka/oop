#include <gtest/gtest.h>
#include "removingVowels.h"
#include <string>


std::string removingVowels(std::string string);

TEST(RemovingVowelsTest, OnlyConsonants) {
    EXPECT_EQ(removingVowels("bcdfgh"), "bcdfgh");
}

TEST(RemovingVowelsTest, OnlyVowels) {
    EXPECT_EQ(removingVowels("aeiouyAEIOUY"), "");
}

TEST(RemovingVowelsTest, MixedString) {
    EXPECT_EQ(removingVowels("Hello World"), "Hll Wrld");
}

TEST(RemovingVowelsTest, EmptyString) {
    EXPECT_EQ(removingVowels(""), "");
}

TEST(RemovingVowelsTest, NumbersAndSymbols) {
    EXPECT_EQ(removingVowels("123!@# test"), "123!@# tst");
}

TEST(RemovingVowelsTest, AllVowelsLowerCase) {
    EXPECT_EQ(removingVowels("aeiouy"), "");
}

TEST(RemovingVowelsTest, AllVowelsUpperCase) {
    EXPECT_EQ(removingVowels("AEIOUY"), "");
}

TEST(RemovingVowelsTest, StringWithSpaces) {
    EXPECT_EQ(removingVowels("a e i o u y"), "     ");
}

TEST(RemovingVowelsTest, ComplexCase) {
    EXPECT_EQ(removingVowels("Programming is fun!"), "Prgrmmng s fn!");
}

TEST(RemovingVowelsTest, OnlyLetterY) {
    EXPECT_EQ(removingVowels("yY"), "");
}

TEST(RemovingVowelsTest, NoVowelsWithY) {
    EXPECT_EQ(removingVowels("sky fly cry"), "sk fl cr");
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}