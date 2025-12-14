#include <iostream>
#include <set>
#include <fstream>
#include <memory>

#include "npc.hpp"
#include "knight_errant.hpp"
#include "dragon.hpp"
#include "princess.hpp"
#include "visitor.hpp"
#include "factory.hpp"
#include "observer.hpp"

struct NameCompare {
    bool operator()(const std::shared_ptr<NPC>& a, const std::shared_ptr<NPC>& b) const {
        return a->getName() < b->getName();
    }
};

void printDungeon(const std::set<std::shared_ptr<NPC>, NameCompare>& npc_set) {
    std::cout << "\n=== ТЕКУЩЕЕ СОСТОЯНИЕ ПОДЗЕМЕЛЬЯ ===\n";
    std::cout << "Всего существ: " << npc_set.size() << "\n";
    std::cout << "------------------------------------------------\n";
    
    for (const auto& npc : npc_set) {
        std::string status = npc->isAlive() ? "жив" : "мёртв";
        std::string type_str;
        
        switch (npc->getType()) {
            case NPCType::KnightErrantType: type_str = "Рыцарь-странник"; break;
            case NPCType::DragonType: type_str = "Дракон"; break;
            case NPCType::PrincessType: type_str = "Принцесса"; break;
        }
        
        std::cout << type_str << " '" << npc->getName() << "'"
                  << " | Позиция: (" << npc->getX() << ", " << npc->getY() << ")"
                  << " | Статус: " << status << "\n";
    }
}

void createFromFile(std::set<std::shared_ptr<NPC>, NameCompare>& alive_npc, std::istream& is, Factory& factory) {
    std::string line;
    int typeInt;
    std::string unique_name;
    double x, y;
    
    std::cout << "Загрузка NPC из файла...\n";
    
    while (is >> typeInt >> unique_name >> x >> y) {
        std::shared_ptr<NPC> new_npc;
        
        switch (typeInt) {
            case 1:
                new_npc = factory.createKnightErrant(unique_name, x, y);
                break;
            case 2:
                new_npc = factory.createDragon(unique_name, x, y);
                break;
            case 3:
                new_npc = factory.createPrincess(unique_name, x, y);
                break;
            default:
                std::cerr << "Неизвестный тип NPC: " << typeInt << std::endl;
                continue;
        }
        
        if (new_npc) {
            alive_npc.insert(new_npc);
            std::cout << "  Загружен: " << unique_name 
                      << " (" << typeInt << ") в позиции (" 
                      << x << ", " << y << ")\n";
        }
    }
}

void demonstrateBattle(const std::shared_ptr<NPC>& attacker, 
                      const std::shared_ptr<NPC>& defender,
                      const std::shared_ptr<TextObserver>& console_log,
                      const std::shared_ptr<FileObserver>& file_log) {
    
    std::cout << "\nБОЙ: " << attacker->getName() 
              << " атакует " << defender->getName() << "\n";
    
    double distance = attacker->distanceTo(defender);
    std::cout << "  Расстояние между ними: " << distance << " метров\n";
    std::cout << "  Требуемая дистанция для атаки: < 50 метров\n";
    
    if (!attacker->isAlive()) {
        std::cout << "Атакующий уже мёртв!\n";
        return;
    }
    
    if (!defender->isAlive()) {
        std::cout << "Защитник уже мёртв!\n";
        return;
    }
    
    BattleVisitor battle_visitor(defender);
    bool result = attacker->accept(battle_visitor);
    
    if (result) {
        std::cout << "Атака успешна!\n";
    } else {
        std::cout << "Атака не удалась (дистанция слишком велика или правила боя запрещают)\n";
    }
    
    console_log->fightResult(attacker, defender, result);
    file_log->fightResult(attacker, defender, result);
}

int main() {
    std::cout << "=== BALAGUR FATE 3 - РЕДАКТОР ПОДЗЕМЕЛЬЯ ===\n";
    
    Factory factory;
    auto console_log = std::make_shared<TextObserver>();
    auto file_log = std::make_shared<FileObserver>("battle_log.txt");
    
    std::cout << "1. СОЗДАНИЕ НАЧАЛЬНОГО ПОДЗЕМЕЛЬЯ\n";
    
    auto knight1 = factory.createKnightErrant("Сэр Гром", 50, 50);
    auto knight2 = factory.createKnightErrant("Ланцелот", 51, 51);
    auto dragon1 = factory.createDragon("Леголас", 52, 52);
    auto dragon2 = factory.createDragon("Смауг", 54, 54);
    auto princess1 = factory.createPrincess("Артур", 55, 55);
    auto princess2 = factory.createPrincess("Гвиневра", 56, 56);
    
    std::set<std::shared_ptr<NPC>, NameCompare> alive_npc;
    alive_npc.insert(knight1);
    alive_npc.insert(knight2);
    alive_npc.insert(dragon1);
    alive_npc.insert(dragon2);
    alive_npc.insert(princess1);
    alive_npc.insert(princess2);
    
    printDungeon(alive_npc);
    
    std::cout << "\n2. СОХРАНЕНИЕ ПОДЗЕМЕЛЬЯ В ФАЙЛ\n";
    
    std::ofstream out_npc_file("npc_save.txt");
    if (!out_npc_file) {
        std::cerr << "Ошибка открытия файла для записи!" << std::endl;
        return 1;
    }
    
    for (const auto& npc : alive_npc) {
        factory.saveToFile(npc, out_npc_file);
    }
    
    out_npc_file.close();
    std::cout << "Подземелье сохранено в файл 'npc_save.txt'\n";
    
    std::cout << "\n3. ЗАГРУЗКА ПОДЗЕМЕЛЬЯ ИЗ ФАЙЛА\n";
    
    std::set<std::shared_ptr<NPC>, NameCompare> loaded_npc;
    
    std::ifstream in_npc_file("npc_save.txt");
    if (!in_npc_file) {
        std::cerr << "Ошибка открытия файла для чтения!" << std::endl;
        return 1;
    }
    
    createFromFile(loaded_npc, in_npc_file, factory);
    in_npc_file.close();
    
    printDungeon(loaded_npc);
    
    std::cout << "\n4. ДЕМОНСТРАЦИЯ БОЕВОЙ СИСТЕМЫ\n";
    std::cout << "Дальность атаки: 50 метров\n";
    
    demonstrateBattle(knight1, dragon1, console_log, file_log);
    demonstrateBattle(dragon2, princess2, console_log, file_log);
    demonstrateBattle(dragon1, dragon2, console_log, file_log);
    demonstrateBattle(knight1, knight2, console_log, file_log);
    demonstrateBattle(princess1, dragon1, console_log, file_log);
    
    std::cout << "\n5. ИТОГОВОЕ СОСТОЯНИЕ ПОДЗЕМЕЛЬЯ\n";
    printDungeon(alive_npc);
    
    std::cout << "\n6. СТАТИСТИКА\n";
    
    int alive_count = 0;
    int dead_count = 0;
    
    for (const auto& npc : alive_npc) {
        if (npc->isAlive()) {
            alive_count++;
        } else {
            dead_count++;
        }
    }
    
    std::cout << "Живых существ: " << alive_count << "\n";
    std::cout << "Мёртвых существ: " << dead_count << "\n";
    std::cout << "Лог битв сохранён в файл: 'battle_log.txt'\n";
    
    std::cout << "=== ДЕМОНСТРАЦИЯ ЗАВЕРШЕНА ===\n";
    
    return 0;
}