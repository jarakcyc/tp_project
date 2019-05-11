#include "items.h"
#include <iostream>
#include <algorithm>

using namespace std;

Item::Item(Hero* _owner, const int _item_id, const string _name, const item_type _type, const string _desc) :
    owner(_owner),
    item_id(_item_id),
    name(_name),
    type(_type),
    description(_desc)
{}

void Item::info() const {
    cout << "item_id: " << item_id << endl;
    cout << "type: ";
    if (type == item_type::WEAPON) {
        cout << "Weapon" << endl;
    } else {
        cout << "Accessory" << endl;
    }
    cout << "name: " << name << endl;
    cout << description << endl;
}

Weapon::Weapon(Hero* _owner, const int _id, const string _name, const string _desc) :
    Item(_owner, _id, _name, item_type::WEAPON, _desc)
{}

Accessory::Accessory(Hero* _owner, const int _id, const string _name, const string _desc) :
    Item(_owner, _id, _name, item_type::ACCESSORY, _desc)
{}


// Warmace of Menethil
Warmace::Warmace(Hero* _owner):
    Weapon(_owner, 1, "Warmace of Menethil", "damage bonus +200, health bonus +500")
{
    add_effect();
}

Warmace::~Warmace() {
    rm_effect();
}

void Warmace::add_effect() {
    owner->damage += 200;
    owner->health += 500;
    owner->max_health += 500;
}

void Warmace::rm_effect() {
    owner->damage -= 200;
    owner->max_health -= 500;
    owner->health = min(owner->health, owner->max_health);
}

//Shadowmourne
Shadowmourne::Shadowmourne(Hero* _owner) :
    Weapon(_owner, 2, "Shadowmourne", "damage bonus + 500")
{
    add_effect();
}

Shadowmourne::~Shadowmourne() {
    rm_effect();
}

void Shadowmourne::add_effect() {
    owner->damage += 500;
}

void Shadowmourne::rm_effect() {
    owner->damage -= 500;
}

//Deathbringer's Will
DeathbringersWill::DeathbringersWill(Hero* _owner):
    Accessory(_owner, 3, "Deathbringer's Will", "damage +50 for all enemies in battle")
{}

void DeathbringersWill::visit(Warrior* unit) {
    unit->health -= 50;
}

//Flask
Flask::Flask(Hero* _owner) :
    Accessory(_owner, 4, "Flask of Professor Putricide", "heal effect +100")
{}

void Flask::visit(Warrior* unit) {
    unit->health = max(unit->health, unit->max_health);
}