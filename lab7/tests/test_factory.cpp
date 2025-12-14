#include <gtest/gtest.h>
#include <sstream>
#include "factory.hpp"
#include "knight_errant.hpp"
#include "dragon.hpp"
#include "princess.hpp"

TEST(FactoryTest, CreateKnightFunction) {
    Factory factory;
    auto knight = factory.createKnightErrant("Arthur", 100, 200);
    
    EXPECT_NE(knight, nullptr);
    EXPECT_EQ(knight->getName(), "Arthur");
    EXPECT_EQ(knight->getType(), NPCType::KnightErrantType);
}

TEST(FactoryTest, CreateDragonFunction) {
    Factory factory;
    auto dragon = factory.createDragon("Smaug", 300, 400);
    
    EXPECT_NE(dragon, nullptr);
    EXPECT_EQ(dragon->getName(), "Smaug");
    EXPECT_EQ(dragon->getType(), NPCType::DragonType);
}

TEST(FactoryTest, CreatePrincessFunction) {
    Factory factory;
    auto princess = factory.createPrincess("Elsa", 500, 600);
    
    EXPECT_NE(princess, nullptr);
    EXPECT_EQ(princess->getName(), "Elsa");
    EXPECT_EQ(princess->getType(), NPCType::PrincessType);
}

TEST(FactoryTest, SaveToFileFunction) {
    Factory factory;
    auto npc = factory.createKnightErrant("Test", 123, 456);
    std::stringstream ss;
    
    factory.saveToFile(npc, ss);
    
    std::string result;
    std::getline(ss, result);
    EXPECT_EQ(result, "3 Test 123 456");
}