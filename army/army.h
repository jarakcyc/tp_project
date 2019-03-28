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

class Hero : public Warrior {
public:
    Hero(string _name, int _health, int _damage);
    ~Hero();
    const int max_weapon = 1;
    const int max_accessory = 1;
    vector<Item*> items;
};

class HeroBuilder {
public:
    Hero* hero;

    void set_hero(Hero* _hero);
    void add_item(const int _id);
    void remove_item(const int _id);
};

class ArmyFactory {
public:
    virtual ~ArmyFactory() {};
    virtual Infantry* create_infantry(const string _name) = 0;
    virtual Distance* create_distance(const string _name) = 0;
    virtual Hero* create_hero(const string _name) = 0;
};

class Army {
public:
    ~Army();

    vector<Infantry*> infantry;
    vector<Distance*> distance;
    vector<Hero*> hero;

    void add_infantry(ArmyFactory* factory, const string _name);
    void add_distance(ArmyFactory* factory, const string _name);
    void add_hero(ArmyFactory* factory, const string _name);
};