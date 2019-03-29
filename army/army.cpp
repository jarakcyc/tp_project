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
    cout << "name: " << name << endl;
    cout << "health: " << health << endl;
    cout << "damage: " << damage << endl;
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

Hero::~Hero() {
    delete weapon;
    delete accessory;
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

// Army
void Army::add_infantry(ArmyFactory* factory, const string _name) {
    Infantry* unit = factory->create_infantry(_name);
    if (unit != nullptr) {
        infantry.push_back(unit);
    }
}

void Army::add_distance(ArmyFactory* factory, const string _name) {
    Distance* unit = factory->create_distance(_name);
    if (unit != nullptr) {
        distance.push_back(unit);
    }
}

Army::~Army() {
    for (int i = 0; i < (int)infantry.size(); ++i) {
        delete infantry[i];
    }
    for (int i = 0; i < (int)distance.size(); ++i) {
        delete distance[i];
    }
}
