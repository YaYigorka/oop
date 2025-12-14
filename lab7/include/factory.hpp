#pragma once

#include <memory>


class NPC;
class KnightErrant;
class Dragon;
class Princess;


class Factory {
public:
    ~Factory() = default;

    std::shared_ptr<NPC> createFromStream(std::istream& is);

    std::shared_ptr<NPC> createNPC(int typeInt, std::string& unique_name, double x, double y);

    std::shared_ptr<KnightErrant> createKnightErrant(const std::string& unique_name, double x, double y);
    std::shared_ptr<Dragon> createDragon(const std::string& unique_name, double x, double y);
    std::shared_ptr<Princess> createPrincess(const std::string& unique_name, double x, double y);

    static void saveToFile(const std::shared_ptr<NPC>& npc, std::ostream& os);
};