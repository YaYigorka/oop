#include <math.h>

#include "dragon.hpp"
#include "visitor.hpp"


Dragon::Dragon(NPCType type, const std::string& unique_name, double x, double y)
    : NPC(NPCType::DragonType, unique_name, x, y)
{
}


bool Dragon::accept(Visitor& visitor) {
    return visitor.visit(this);
}


double Dragon::distanceTo(const std::shared_ptr<NPC>& other) const {
    double x = other->getX();
    double y = other->getY();

    return std::sqrt(std::pow(getX() - x, 2) + std::pow(getY() - y, 2));
}