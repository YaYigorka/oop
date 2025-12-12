#include <iostream>

#include "observer.hpp"
#include "npc.hpp"


void TextObserver::fightResult(const std::shared_ptr<NPC>& attacker, const std::shared_ptr<NPC>& defender, bool success) {
    if (success) {
        std::cout << attacker->getType() << " " << attacker->getName() << " killed " << defender->getType() << " " << defender->getName() << " at (" << defender->getX() << ", " << defender->getY() << ")\n";
    }
}


FileObserver::FileObserver(const std::string& filename)
    : logfile_{filename, std::ios::app}
{
}


FileObserver::~FileObserver() {
    if (logfile_.is_open()) {
        logfile_.close();
    }
}


void FileObserver::fightResult(const std::shared_ptr<NPC>& attacker, const std::shared_ptr<NPC>& defender, bool success) {
    if (logfile_.is_open() && success) {
        logfile_ << attacker->getType() << " " << attacker->getName() 
                << " killed " << defender->getType() << " " << defender->getName() 
                << " at (" << defender->getX() << ", " << defender->getY() << ")\n";
    }
}