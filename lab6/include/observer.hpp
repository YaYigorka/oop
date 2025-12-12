#pragma once

#include <memory>
#include <fstream>


class NPC;


class IFightObserver {
public:
    virtual ~IFightObserver() = default;

    virtual void fightResult(const std::shared_ptr<NPC>& attacker, const std::shared_ptr<NPC>& defender, bool success) = 0;
};


class TextObserver : public IFightObserver {
public:
    void fightResult(const std::shared_ptr<NPC>& attacker, const std::shared_ptr<NPC>& defender, bool success) override;
};


class FileObserver : public IFightObserver {
private:
    std::ofstream logfile_;

public:
    FileObserver(const std::string& filename = "log.txt");
    ~FileObserver();

    void fightResult(const std::shared_ptr<NPC>& attacker, const std::shared_ptr<NPC>& defender, bool success) override;
};