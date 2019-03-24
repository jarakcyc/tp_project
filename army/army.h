#pragma once
#include "items.h"
#include <string>
#include <vector>

using namespace std;

class Item;

enum warrior_type {
    INFANTRY,
    DISTANCE,
    HERO
};

class Warrior {
public:
    Warrior();
    Warrior(string _name, warrior_type _type, int _health, int _damage, int _cost);
    void info() const;
    string name;
    warrior_type type;
    int max_health;
    int health;
    int damage;
    int cost;
};

class Infantry : public Warrior {
public:
    Infantry(string _name, int _health, int _damage);
};

class Distance : public Warrior {
public:
    Distance(string _name, int _health, int _damage);
};

class ArmyFactory {
public:
    virtual ~ArmyFactory() {};
    virtual Infantry* create_infantry(string name) = 0;
    virtual Distance* create_distance(string name) = 0;
};

class Hero : public Warrior {
public:
    Hero(string _name, int _health, int _damage);
    ~Hero();
    void add_item(const int _id);
    void remove_item(const int _id);
    vector<Item*> items;
};
