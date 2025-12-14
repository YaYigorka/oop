#pragma once

#include <string>
#include <memory>


class Visitor;

enum NPCType {
    PrincessType = 1,
    DragonType = 2,
    KnightErrantType = 3
};

struct NPCLocation {
    double x;
    double y;
};


class NPC : public std::enable_shared_from_this<NPC> {
protected:
    const NPCType npc_type_;
    const std::string unique_name_;
    NPCLocation npc_location_;
    bool alive;

public:
    NPC(NPCType type, const std::string& unique_name, double x, double y);
    virtual ~NPC() = default;

    virtual bool accept(Visitor& visitor) = 0;
    virtual void kill_npc() { alive = false; }

    virtual void setX(double x) { npc_location_.x = x; }
    virtual void setY(double y) { npc_location_.y = y; }

    virtual std::string getName() const { return unique_name_; }
    virtual double getX() const { return npc_location_.x; }
    virtual double getY() const { return npc_location_.y; }
    virtual bool isAlive() const { return alive == true; }
    virtual NPCType getType() const { return npc_type_; }
    virtual double distanceTo(const std::shared_ptr<NPC>& other) const = 0;
};  