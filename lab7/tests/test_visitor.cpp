#include <gtest/gtest.h>
#include "factory.hpp"
#include "visitor.hpp"
#include "knight_errant.hpp"
#include "dragon.hpp"
#include "princess.hpp"

TEST(VisitorTest, AcceptFunction) {
    Factory factory;
    auto knight = factory.createKnightErrant("Knight", 0, 0);
    auto dragon = factory.createDragon("Dragon", 10, 0);
    
    BattleVisitor visitor(dragon);
    bool result = knight->accept(visitor);
    
    EXPECT_TRUE(result);
}

TEST(BattleTest, KnightCanKillDragon) {
    Factory factory;
    auto knight = factory.createKnightErrant("Knight", 0, 0);
    auto dragon = factory.createDragon("Dragon", 10, 0);
    
    BattleVisitor visitor(dragon);
    bool result = knight->accept(visitor);
    
    EXPECT_TRUE(result);
    EXPECT_FALSE(dragon->isAlive());
    EXPECT_TRUE(knight->isAlive());
}

TEST(BattleTest, DragonCanKillPrincess) {
    Factory factory;
    auto dragon = factory.createDragon("Dragon", 0, 0);
    auto princess = factory.createPrincess("Princess", 10, 0);
    
    BattleVisitor visitor(princess);
    bool result = dragon->accept(visitor);
    
    EXPECT_TRUE(result);
    EXPECT_FALSE(princess->isAlive());
    EXPECT_TRUE(dragon->isAlive());
}

TEST(BattleTest, TooFarToAttack) {
    Factory factory;
    auto knight = factory.createKnightErrant("Knight", 0, 0);
    auto dragon = factory.createDragon("Dragon", 100, 0);
    
    BattleVisitor visitor(dragon);
    bool result = knight->accept(visitor);
    
    EXPECT_FALSE(result);
    EXPECT_TRUE(dragon->isAlive());
}

TEST(BattleTest, DeadCannotAttack) {
    Factory factory;
    auto knight = factory.createKnightErrant("Knight", 0, 0);
    auto dragon = factory.createDragon("Dragon", 10, 0);
    
    knight->kill_npc();
    
    BattleVisitor visitor(dragon);
    bool result = knight->accept(visitor);
    
    EXPECT_FALSE(result);
    EXPECT_TRUE(dragon->isAlive());
}