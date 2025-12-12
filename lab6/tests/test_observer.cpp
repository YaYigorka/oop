#include <gtest/gtest.h>
#include <sstream>
#include <fstream>
#include "factory.hpp"
#include "observer.hpp"
#include "knight_errant.hpp"
#include "dragon.hpp"
#include "princess.hpp"

TEST(ObserverTest, ConsoleLogFunction) {
    Factory factory;
    auto attacker = factory.createKnightErrant("Attacker", 0, 0);
    auto defender = factory.createDragon("Defender", 10, 0);
    
    testing::internal::CaptureStdout();
    
    TextObserver observer;
    observer.fightResult(attacker, defender, true);
    
    std::string output = testing::internal::GetCapturedStdout();
    
    EXPECT_NE(output.find("Attacker"), std::string::npos);
    EXPECT_NE(output.find("Defender"), std::string::npos);
}

TEST(ObserverTest, FileLogFunction) {
    Factory factory;
    auto attacker = factory.createKnightErrant("Attacker", 0, 0);
    auto defender = factory.createDragon("Defender", 10, 0);
    
    std::string filename = "test_log.txt";
    std::remove(filename.c_str());
    
    {
        FileObserver observer(filename);
        observer.fightResult(attacker, defender, true);
    }
    
    std::ifstream file(filename);
    EXPECT_TRUE(file.good());
    
    std::string line;
    std::getline(file, line);
    EXPECT_NE(line.find("Attacker"), std::string::npos);
    
    file.close();
    std::remove(filename.c_str());
}

TEST(ObserverTest, NoLogOnFailedBattle) {
    Factory factory;
    auto attacker = factory.createKnightErrant("Attacker", 0, 0);
    auto defender = factory.createDragon("Defender", 10, 0);
    
    testing::internal::CaptureStdout();
    
    TextObserver observer;
    observer.fightResult(attacker, defender, false);
    
    std::string output = testing::internal::GetCapturedStdout();
    
    EXPECT_TRUE(output.empty());
}