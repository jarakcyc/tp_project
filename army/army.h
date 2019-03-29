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
    Item* weapon;
    Item* accessory;
};

class HeroBuilder {
public:
    HeroBuilder(){}
    virtual ~HeroBuilder(){}
    Hero* hero;
    void set_hero(Hero* _hero);
    virtual void add_weapon() = 0;
    virtual void add_accessory() = 0;
};

class TankBuilder : public HeroBuilder {
public:
    void add_weapon() override;
    void add_accessory() override;
};

class DamagerBuilder : public HeroBuilder {
public:
    void add_weapon() override;
    void add_accessory() override;
};

class HealBuilder : public HeroBuilder {
public:
    void add_weapon() override;
    void add_accessory() override;
};

class HeroManager {
private:
    HeroBuilder* builder;
public:
    void set_HeroBuilder(HeroBuilder* _builder);
    Hero* create_hero();
};

class ArmyFactory {
public:
    virtual ~ArmyFactory() {}
    virtual Infantry* create_infantry(const string _name) = 0;
    virtual Distance* create_distance(const string _name) = 0;
};

class Army {
public:
    ~Army();

    vector<Infantry*> infantry;
    vector<Distance*> distance;
    Hero* hero = nullptr;

    void add_infantry(ArmyFactory* factory, const string _name);
    void add_distance(ArmyFactory* factory, const string _name);
};