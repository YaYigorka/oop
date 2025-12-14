#include <math.h>

#include "knight_errant.hpp"
#include "visitor.hpp"


KnightErrant::KnightErrant(NPCType type, const std::string& unique_name, double x, double y)
    : NPC(NPCType::KnightErrantType, unique_name, x, y)
{
}


bool KnightErrant::accept(Visitor& visitor) {
     return visitor.visit(this);
}


double KnightErrant::distanceTo(const std::shared_ptr<NPC>& other) const {
    double x = other->getX();
    double y = other->getY();

    return std::sqrt(std::pow(getX() - x, 2) + std::pow(getY() - y, 2));
}