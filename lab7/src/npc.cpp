#include "npc.hpp"


NPC::NPC(NPCType type, const std::string& unique_name, double x, double y)
    : npc_type_{type}
    , unique_name_{unique_name}
    , npc_location_{x, y}
    , alive(true)
{
}