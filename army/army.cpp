#include "army.h"
#include <iostream>
#include <string>

using namespace std;

Warrior::Warrior(string _name, warrior_type _type, int _health, int _max_health, int _damage, int _cost) :
    name(_name),
    type(_type),
    max_health(_max_health),
    health(_health),
    damage(_damage),
    cost(_cost)
{}

Warrior::Warrior(string _name, warrior_type _type, int _health, int _damage, int _cost) :
    name(_name),
    type(_type),
    max_health(_health),
    health(_health),
    damage(_damage),
    cost(_cost)
{}

void Warrior::info() const {
    cout << "{name: " << name << "; ";
    cout << "health: " << health << "; ";
    cout << "damage: " << damage << "; ";
    cout << "target: " << target << "}" << endl;
}

void Warrior::accept(Item* item) {
    item->visit(this);
}

Infantry::Infantry(string _name, int _health, int _damage) :
    Warrior(_name, warrior_type::INFANTRY, _health, _damage, 100)
{}

Distance::Distance(string _name, int _health, int _damage) :
    Warrior(_name, warrior_type::DISTANCE, _health, _damage, 200)
{}

Hero::Hero(string _name, int _health, int _damage) :
    Warrior(_name, warrior_type::HERO, _health, _damage, 1000)
{}

Infantry* ArmyFactory::create_infantry(const string _name) {
    Infantry* unit = nullptr;

    for (int i = 0; i < (int)i_list.size(); ++i) {
        if (i_list[i].name == _name) {
            unit = new Infantry(i_list[i].name, i_list[i].health, i_list[i].damage);
            break;
        }
    }

    if (unit == nullptr) {
        cout << "no units with the same name" << endl;
    }
    return unit;
}

Distance* ArmyFactory::create_distance(const string _name) {
    Distance* unit = nullptr;

    for (int i = 0; i < (int)d_list.size(); ++i) {
        if (d_list[i].name == _name) {
            unit = new Distance(d_list[i].name, d_list[i].health, d_list[i].damage);
            break;
        }
    }

    if (unit == nullptr) {
        cout << "no units with the same name" << endl;
    }
    return unit;
}

Hero::~Hero() {
    if (weapon != nullptr) {
        delete weapon;
    }
    if (accessory != nullptr) {
        delete accessory;
    }
}

//Builders
void HeroBuilder::set_hero(Hero* _hero) {
    hero = _hero;
}

void TankBuilder::add_weapon() {hero->weapon = new Warmace(hero);}
void TankBuilder::add_accessory() {hero->accessory = new DeathbringersWill(hero);}

void DamagerBuilder::add_weapon() {hero->weapon = new Shadowmourne(hero);}
void DamagerBuilder::add_accessory() {hero->accessory = new DeathbringersWill(hero);}

void HealBuilder::add_weapon() {hero->weapon = new Warmace(hero);}
void HealBuilder::add_accessory() {hero->accessory = new Flask(hero);}

void HeroManager::set_HeroBuilder(HeroBuilder* _builder) {builder = _builder;}

Hero* HeroManager::create_hero() {
    Hero* hero = new Hero("Hero", 1000, 100);
    builder->set_hero(hero);
    builder->add_weapon();
    builder->add_accessory();
    return hero;
}

void Army::add_infantry(ArmyFactory* factory, const string _name, int& money) {
    Infantry* unit = factory->create_infantry(_name);
    if (unit == nullptr) {
        return;
    }
    if (money >= unit->cost) {
        money -= unit->cost;
        units.push_back(unit);
    } else {
        delete unit;
    }
}

void Army::add_distance(ArmyFactory* factory, const string _name, int& money) {
    Distance* unit = factory->create_distance(_name);
    if (unit == nullptr) {
        return;
    }
    if (money >= unit->cost) {
        money -= unit->cost;
        units.push_back(unit);
    } else {
        delete unit;
    }
}

void Army::add_hero(HeroManager* manager, const string _name, int& money) {
    HeroBuilder* builder = nullptr;
    if (_name == "tank") {
        builder = new TankBuilder();
    } else if (_name == "heal") {
        builder = new HealBuilder();
    } else if (_name == "damager") {
        builder = new DamagerBuilder();
    }

    manager->set_HeroBuilder(builder);
    try {
        Hero* unit = manager->create_hero();
        if (money >= unit->cost) {
            money -= unit->cost;
            units.push_back(unit);
        } else {
            delete unit;
        }
    }
    catch (...) {}
}

Army::~Army() {
    for (int i = 0; i < (int)units.size(); ++i)
        delete units[i];
}

RelaxDecorator::RelaxDecorator(Warrior* unit) :
    Warrior(unit->name, unit->type, unit->health, unit->max_health, unit->damage, unit->cost)
{
    //in_battle = false;
    target = -1;
}

void RelaxDecorator::update() {
    health = max(health + 50, max_health);
}

BattleDecorator::BattleDecorator(Warrior* unit, int _target) :
    Warrior(unit->name, unit->type, unit->health, unit->max_health, unit->damage, unit->cost)
{
    //in_battle = true;
    target = _target;
}