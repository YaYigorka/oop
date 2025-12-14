#include <iostream>
#include <set>
#include <fstream>
#include <memory>
#include <random>
#include <format>
#include <math.h>
#include <mutex>
#include <thread>
#include <atomic>
#include <chrono>

#include "npc.hpp"
#include "knight_errant.hpp"
#include "dragon.hpp"
#include "princess.hpp"
#include "visitor.hpp"
#include "factory.hpp"
#include "observer.hpp"


const int MAP_SIZE = 100;
const int DISPLAY_SIZE = 20;

struct NameCompare {
    bool operator()(const std::shared_ptr<NPC>& a, const std::shared_ptr<NPC>& b) const {
        return a->getName() < b->getName();
    }
};

using AliveNPCSet = std::set<std::shared_ptr<NPC>, NameCompare>;
using DeadNPCSet = std::set<std::shared_ptr<NPC>, NameCompare>;
using gameStatus = std::atomic<bool>;

std::mutex alive_mutex;
std::mutex dead_mutex;
std::mutex cout_mutex;


void create_npc(AliveNPCSet& alive_npc) {
    Factory factory;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(1, MAP_SIZE);

    for (int i = 0; i < 50; ++i) {
        double x = (double)dist(gen);
        double y = (double)dist(gen);
        int typeInt = dist(gen) % 3 + 1;
        std::string npc = "npc";
        std::string unique_name = std::format("{}{}", npc, i + 1);
        alive_npc.insert(factory.createNPC(typeInt, unique_name, x, y));
    }
}


void movementLogic(AliveNPCSet& alive_npc, gameStatus& running) {
    std::random_device rd;
    std::mt19937 gen(rd());

    while (running) {
        {
            std::lock_guard<std::mutex> alive_lock(alive_mutex);

            for (auto npc : alive_npc) {

                if (!npc->isAlive()) {
                    continue;
                }

                int max_move;
                switch(npc->getType()) {
                    case KnightErrantType:
                        max_move = 30;
                        break;
                    case DragonType:
                        max_move = 50;
                        break;
                    default:
                        max_move = 1;
                        break;
                }

                std::uniform_int_distribution<int> dist(-max_move, max_move);
                double dx = dist(gen);
                double dy = dist(gen);

                int new_x = npc->getX() + dx;
                int new_y = npc->getY() + dy;

                new_x = new_x > MAP_SIZE ? MAP_SIZE : new_x;
                new_x = new_x < 0 ? 0 : new_x;
                new_y = new_y > MAP_SIZE ? MAP_SIZE : new_y;
                new_y = new_y < 0 ? 0 : new_y;

                npc->setX(new_x);
                npc->setY(new_y);
            }
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
}


int rollDice() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(1, 6);

    return dist(gen);
}

void battleLogic(AliveNPCSet& alive_npc, DeadNPCSet& dead_npc, gameStatus& running) {
    while (running) {
        {
            std::lock_guard<std::mutex> alive_lock(alive_mutex);
            for (auto attaker : alive_npc) {
                if (!attaker->isAlive()) {
                    continue;
                }

                for (auto defender : alive_npc) {

                    if (attaker->getName() == defender->getName()) {
                        continue;
                    }

                    if (!defender->isAlive()) {
                        continue;
                    }

                    int attack_power = rollDice();
                    int defender_power = rollDice();

                    if (defender_power >= attack_power) {
                        continue;
                    }

                    std::lock_guard<std::mutex> dead_lock(dead_mutex);
                    BattleVisitor battle_visitor(defender);
                    bool result = attaker->accept(battle_visitor);
                    if (result) {
                        dead_npc.insert(defender);
                    }
                }
            }
        }
        
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
}


void mapLogic(AliveNPCSet& alive_npc) {
    std::vector<std::vector<char>> npc_map_vector{DISPLAY_SIZE, std::vector<char>(DISPLAY_SIZE, '-')};
    std::lock_guard<std::mutex> alive_lock(alive_mutex);
    for (auto npc : alive_npc) {

        if (!npc->isAlive()) {
            continue;
        }

        int x = npc->getX();
        x = x > 0 ? x % 20 : 0;
        int y = npc->getY();
        y = y > 0 ? y % 20 : 0;

        if (npc_map_vector[x][y] == 'x') {
            continue;
        }

        npc_map_vector[x][y] = 'x';
    }
    
    std::lock_guard<std::mutex> cout_lock(cout_mutex);
    for (auto i : npc_map_vector) {
        std::cout << "|";
        for (auto j : i) {
            std::cout << j;
        }

        std::cout << "|" <<std::endl;
    }

    for (int i = 0; i < DISPLAY_SIZE + 2; ++i) {
        std::cout << "=";
    }

    std::cout << std::endl;
}


void printAliveNPC(AliveNPCSet& alive_npc) {
    std::cout << "\n\n=====Alive NLP=====\n\n";
    for (auto& npc : alive_npc) {
        if (npc->isAlive()) {
            std::cout << "NAME: " << npc->getName() << " TYPE: " << npc->getType() << std::endl;
        }
    }
}


int main() {
    std::cout << "===Starting the game===" << std::endl;
    AliveNPCSet alive_npc;
    DeadNPCSet dead_npc;
    create_npc(alive_npc);
    gameStatus running{true};

    std::thread movement_thread(movementLogic, std::ref(alive_npc), std::ref(running));
    std::thread battle_thread(battleLogic, std::ref(alive_npc), std::ref(dead_npc), std::ref(running));
    
    auto start = std::chrono::steady_clock::now();
    
    while (true) {
        auto now = std::chrono::steady_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::seconds>(now - start);
        
        if (elapsed.count() >= 30) {
            break;
        }
        
        mapLogic(alive_npc);
        
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    
    running = false;
    std::cout << "=====Game over=====" << std::endl;
    
    movement_thread.join();
    battle_thread.join();

    printAliveNPC(alive_npc);
}