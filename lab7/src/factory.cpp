#include <iostream>

#include "npc.hpp"
#include "factory.hpp"
#include "knight_errant.hpp"
#include "dragon.hpp"
#include "princess.hpp"


std::shared_ptr<NPC> Factory::createFromStream(std::istream& is) {
    int typeInt;
    std::string unique_name;
    double x, y;
    is >> typeInt >> unique_name >> x >> y;

    NPCType type = static_cast<NPCType>(typeInt);
    switch (type) {
        case NPCType::KnightErrantType:
            return createKnightErrant(unique_name, x, y);
        case NPCType::DragonType:
            return createDragon(unique_name, x, y);
        case NPCType::PrincessType:
            return createPrincess(unique_name, x, y);
    }
}


std::shared_ptr<NPC> Factory::createNPC(int typeInt, std::string& unique_name, double x, double y) {
    NPCType type = static_cast<NPCType>(typeInt);
    switch (type) {
        case NPCType::KnightErrantType:
            return createKnightErrant(unique_name, x, y);
        case NPCType::DragonType:
            return createDragon(unique_name, x, y);
        case NPCType::PrincessType:
            return createPrincess(unique_name, x, y);
    }
}


std::shared_ptr<KnightErrant> Factory::createKnightErrant(const std::string& unique_name, double x, double y) {
    return std::make_shared<KnightErrant>(NPCType::KnightErrantType, unique_name, x, y);
}


std::shared_ptr<Dragon> Factory::createDragon(const std::string& unique_name, double x, double y) {
    return std::make_shared<Dragon>(NPCType::DragonType, unique_name, x, y);
}


std::shared_ptr<Princess> Factory::createPrincess(const std::string& unique_name, double x, double y) {
    return std::make_shared<Princess>(NPCType::PrincessType, unique_name, x, y);
}


void Factory::saveToFile(const std::shared_ptr<NPC>& npc, std::ostream& os) {
    if (npc) {
        os << npc->getType()<< " " << npc->getName() << " " << npc->getX() << " " << npc->getY() << "\n";
    }
}