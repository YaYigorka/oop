#include "visitor.hpp"
#include "npc.hpp"
#include "knight_errant.hpp"
#include "dragon.hpp"
#include "princess.hpp"


BattleVisitor::BattleVisitor(const std::shared_ptr<NPC>& defender)
    : defender_{defender}
{
}


bool BattleVisitor::visit(KnightErrant* knight_errant) {
    if (!knight_errant->isAlive() || !defender_->isAlive()) {
        return false;
    }

    if (knight_errant->distanceTo(defender_) > 50) {
        return false;
    }

    if (auto* otherKnight = dynamic_cast<KnightErrant*>(defender_.get())) {
        otherKnight->kill_npc();
        knight_errant->kill_npc();
        return true;
    } else if (auto* dragon = dynamic_cast<Dragon*>(defender_.get())) {
        dragon->kill_npc();
        return true;
    } else if (auto* princess = dynamic_cast<Princess*>(defender_.get())) {
        return true;
    }
}


bool BattleVisitor::visit(Dragon* dragon) {
    if (!dragon->isAlive() || !defender_->isAlive()) {
        return false;
    }

    if (dragon->distanceTo(defender_) > 50) {
        return false;
    }

    if (auto* knight_errant = dynamic_cast<KnightErrant*>(defender_.get())) {
        defender_->kill_npc();
        return true;
    } else if (auto* otherDragon = dynamic_cast<Dragon*>(defender_.get())) {
        otherDragon->kill_npc();
        dragon->kill_npc();
        return true;
    } else if (auto* princess = dynamic_cast<Princess*>(defender_.get())) {
        princess->kill_npc();
        return true;
    }
}


bool BattleVisitor::visit(Princess* princess) {
    if (!princess->isAlive() || !defender_->isAlive()) {
        return false;
    }

    if (princess->distanceTo(defender_) > 50) {
        return false;
    }

    if (auto* knight_errant = dynamic_cast<KnightErrant*>(defender_.get())) {
        return true;
    } else if (auto* dragon = dynamic_cast<Dragon*>(defender_.get())) {
        princess->kill_npc();
        return true;
    } else if (auto* princess = dynamic_cast<Princess*>(defender_.get())) {
        return true;
    }
}