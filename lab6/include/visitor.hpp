#pragma once

#include <memory>


class NPC;
class KnightErrant;
class Dragon;
class Princess;


class Visitor {
public:
    virtual ~Visitor() = default;

    virtual bool visit(KnightErrant* knight_errant) = 0;
    virtual bool visit(Dragon* dragon) = 0;
    virtual bool visit(Princess* princess) = 0;
};


class BattleVisitor : public Visitor{
private:
    std::shared_ptr<NPC> defender_;
    
public:
    BattleVisitor(const std::shared_ptr<NPC>& defender);

    bool visit(KnightErrant* knight_errant) override;
    bool visit(Dragon* dragon) override;
    bool visit(Princess* princess) override;
};