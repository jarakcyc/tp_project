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
    cout << "attack: " << damage << endl;
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
    while (!items.empty()) {
        delete (items.back());
        items.pop_back();
    }
}

void Hero::add_item(const int _id) {
    if (_id == 1) {
        Item* ptr = new Warmace(this);
        items.push_back(ptr);
    } else if (_id == 2) {
        Item* ptr = new DeathbringersWill(this);
        items.push_back(ptr);
    } else {
        cout << "no such item" << endl;
    }
}

void Hero::remove_item(const int id) {
    for (int i = 0; i < (int)items.size(); ++i) {
        if (items[i]->item_id == id) {
            items.erase(items.begin() + i);
            break;
        }
    }
}
