#pragma once

#include "npc.hpp"


class Dragon : public NPC {
public:
    Dragon(NPCType type, const std::string& unique_name, double x, double y);

    virtual bool accept(Visitor& visitor) override;

    virtual double distanceTo(const std::shared_ptr<NPC>& other) const override;
};