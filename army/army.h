#pragma once
#include "items.h"
#include <string>
#include <vector>
#include <deque>
#include <iostream>

using namespace std;

class Item;

enum warrior_type {
    INFANTRY,
    DISTANCE,
    HERO
};

class Warrior {
public:
    Warrior() {};
    virtual ~Warrior() {};
    Warrior(string _name, warrior_type _type, int _health, int _mah_health, int _damage, int _cost);
    Warrior(string _name, warrior_type _type, int _health, int _damage, int _cost);

    virtual void info() const;
    virtual void update() {};

    void accept(Item* item);

    string name;
    warrior_type type;
    int max_health;
    int health;
    int damage;
    int cost;
    //bool in_battle = false;
    int target = -1; // -1 if unit relax

    Item* weapon = nullptr;
    Item* accessory = nullptr;
};

class RelaxDecorator : public Warrior {
public:
    RelaxDecorator(Warrior* _unit);
    void update() override;
};

class BattleDecorator : public Warrior {
public:
    BattleDecorator(Warrior* _unit, int _target);
    void update() override {};
};

class Infantry : public Warrior {
public:
    Infantry(string _name, int _health, int _damage);
};

class Distance : public Warrior {
public:
    Distance(string _name, int _health, int _damage);
};

// Hero

class Hero : public Warrior {
public:
    Hero(string _name, int _health, int _damage);
    ~Hero();
    //Item* weapon = nullptr;
    //Item* accessory = nullptr;
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

// Army

class ArmyFactory {
public:
    ~ArmyFactory() {}
    vector<Infantry> i_list;
    vector<Distance> d_list;
    Infantry* create_infantry(const string _name);
    Distance* create_distance(const string _name);
};

class Army {
public:
    ~Army();
    vector<Warrior*> units;
    void add_infantry(ArmyFactory* factory, const string _name, int& money);
    void add_distance(ArmyFactory* factory, const string _name, int& money);
    void add_hero(HeroManager* manager, const string _name, int& money);
};