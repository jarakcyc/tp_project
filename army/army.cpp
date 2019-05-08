#include "army.h"
#include <iostream>
#include <string>

using namespace std;

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
    cout << " health: " << health << "; ";
    cout << " damage: " << damage << "}" << endl;
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

// Barracks
void Barracks::add_infantry(ArmyFactory* factory, const string _name) {
    Infantry* unit = factory->create_infantry(_name);
    if (unit != nullptr) {
        infantry.push_back(unit);
    }
}

void Barracks::add_distance(ArmyFactory* factory, const string _name) {
    Distance* unit = factory->create_distance(_name);
    if (unit != nullptr) {
        distance.push_back(unit);
    }
}

Barracks::~Barracks() {
    for (int i = 0; i < (int)infantry.size(); ++i) {
        delete infantry[i];
    }
    for (int i = 0; i < (int)distance.size(); ++i) {
        delete distance[i];
    }
    for (int i = 0; i < (int)heroes.size(); ++i) {
        delete heroes[i];
    }
}

// Squad 
Squad::Squad(const string _name) {
    name = _name;
}

void Squad::add(ISquad* unit) {
    units.push_back(unit);
    unit->squad_name = name;
}

void Squad::remove(ISquad* unit) {
    int id = -1;
    for (int i = 0; i < (int)units.size(); ++i) {
        if (units[i] == unit) {
            id = i;
            break;
        }
    }
    if (id != -1) {
        units[id]->squad_name = "";
        units.erase(units.begin() + id);
    }
}

void RelaxDecorator::update() {
    health = max(health + 50, max_health);
}