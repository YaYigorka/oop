#include <gtest/gtest.h>
#include "knight_errant.hpp"
#include "dragon.hpp"
#include "princess.hpp"

TEST(KnightErrantTest, CreateAndGet) {
    KnightErrant knight(NPCType::KnightErrantType, "Sir_Lancelot", 10, 20);
    
    EXPECT_EQ(knight.getName(), "Sir_Lancelot");
    EXPECT_EQ(knight.getType(), NPCType::KnightErrantType);
    EXPECT_EQ(knight.getX(), 10);
    EXPECT_EQ(knight.getY(), 20);
    EXPECT_TRUE(knight.isAlive());
}

TEST(DragonTest, CreateAndGet) {
    Dragon dragon(NPCType::DragonType, "Smaug", 30, 40);
    
    EXPECT_EQ(dragon.getName(), "Smaug");
    EXPECT_EQ(dragon.getType(), NPCType::DragonType);
    EXPECT_EQ(dragon.getX(), 30);
    EXPECT_EQ(dragon.getY(), 40);
    EXPECT_TRUE(dragon.isAlive());
}

TEST(PrincessTest, CreateAndGet) {
    Princess princess(NPCType::PrincessType, "Elsa", 50, 60);
    
    EXPECT_EQ(princess.getName(), "Elsa");
    EXPECT_EQ(princess.getType(), NPCType::PrincessType);
    EXPECT_EQ(princess.getX(), 50);
    EXPECT_EQ(princess.getY(), 60);
    EXPECT_TRUE(princess.isAlive());
}

TEST(NPCTest, KillFunction) {
    KnightErrant knight(NPCType::KnightErrantType, "Knight", 0, 0);
    
    knight.kill_npc();
    EXPECT_FALSE(knight.isAlive());
}

TEST(DistanceTest, CalculateDistance) {
    KnightErrant knight1(NPCType::KnightErrantType, "A", 0, 0);
    auto knight2 = std::make_shared<KnightErrant>(NPCType::KnightErrantType, "B", 3, 4);
    
    EXPECT_NEAR(knight1.distanceTo(knight2), 5.0, 0.001);
}