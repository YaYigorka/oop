#include <math.h>

#include "princess.hpp"
#include "visitor.hpp"


Princess::Princess(NPCType type, const std::string& unique_name, double x, double y)
    : NPC(NPCType::PrincessType, unique_name, x, y)
{
}


bool Princess::accept(Visitor& visitor) {
    return visitor.visit(this);
}


double Princess::distanceTo(const std::shared_ptr<NPC>& other) const {
    double x = other->getX();
    double y = other->getY();

    return std::sqrt(std::pow(getX() - x, 2) + std::pow(getY() - y, 2));
}