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
        cout << "weapon" << endl;
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
    Weapon(_owner, 1, "Warmace of Menethil", "damage bonus +200, health bonus +100")
{
    const_effect();
}

void Warmace::const_effect() {
    owner->damage += 200;
    owner->health += 100;
    owner->max_health += 100;
}

void Warmace::rm_const_effect() {
    owner->damage -= 200;
    owner->max_health -= 100;
    owner->health = min(owner->health, owner->max_health);
}

//Deathbringer's Will
DeathbringersWill::DeathbringersWill(Hero* _owner):
    Accessory(_owner, 2, "Deathbringer's Will", "damage bonus +500 in battle")
{}

void DeathbringersWill::time_effect() {
    owner->damage += 500;
}

void DeathbringersWill::rm_time_effect() {
    owner->damage -= 500;
}
