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
    while (!items.empty()) {
        delete (items.back());
        items.pop_back();
    }
}

void HeroBuilder::set_hero(Hero* _hero) {
    hero = _hero;
}

void HeroBuilder::add_item(const int _id) {
    Item* ptr = nullptr;
    if (_id == 1) {
        ptr = new Warmace(hero);
    } else if (_id == 2) {
        ptr = new Shadowmourne(hero);
    } else if (_id == 3) {
        ptr = new DeathbringersWill(hero);
    } else if (_id == 4) {
        ptr = new Flask(hero);
    }

    if (ptr == nullptr) {
        cout << "no such item" << endl;
    } else {
        int cnt = 0;
        for (Item* it : hero->items) {
            if (ptr->type == it->type) {
                cnt++;
            }
        }
        int max_can = 0;
        if (ptr->type == item_type::WEAPON) {
            max_can = hero->max_weapon;
        } else if (ptr->type == item_type::ACCESSORY) {
            max_can = hero->max_accessory;
        }
        if (cnt < max_can) {
            hero->items.push_back(ptr);
            //cout << "added item: " << endl;
            //ptr->info();
        } else {
            cout << "can't add this item" << endl;
            delete ptr;
        }
    }
}

void HeroBuilder::remove_item(const int _id) {
    for (int i = 0; i < (int)hero->items.size(); ++i) {
        if (hero->items[i]->item_id == _id) {
            delete hero->items[i];
            hero->items.erase(hero->items.begin() + i);
            break;
        }
    }
}

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

void Army::add_hero(ArmyFactory* factory, const string _name) {
    Hero* unit = factory->create_hero(_name);
    if (unit != nullptr) {
        hero.push_back(unit);
    }
}

Army::~Army() {
    for (int i = 0; i < (int)infantry.size(); ++i) {
        delete infantry[i];
    }
    for (int i = 0; i < (int)distance.size(); ++i) {
        delete distance[i];
    }
    for (int i = 0; i < (int)hero.size(); ++i) {
        delete hero[i];
    }
}
