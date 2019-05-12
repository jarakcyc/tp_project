#pragma once
#include "army.h"
#include <string>
#include <iostream>

using namespace std;

class Warrior;
class Hero;

enum item_type {
    WEAPON,
    ACCESSORY
};

class Item {
public:
    Item(Hero* _owner, const int& _item_id, const string& _name, const item_type& _type, const string& _desc);
    virtual ~Item() {};

    Hero* owner;
    const int item_id;
    const string name;
    const item_type type;
    const string description;
    void info() const;

    virtual void add_effect() {};
    virtual void rm_effect() {};

    virtual void visit(Warrior* unit) {};
};

class Weapon : public Item {
public:
    Weapon(Hero* _owner, const int& _id, const string& _name, const string& _desc);
};

class Accessory : public Item {
public:
    Accessory(Hero* _owner, const int& _id, const string& _name, const string& _desc);
};


class Warmace : public Weapon { // id = 1, damage bonus +200, health bonus +500
public:
    Warmace(Hero* _owner);
    ~Warmace();
    void add_effect() override;
    void rm_effect() override;
};

class Shadowmourne : public Weapon { // id = 2, damage bonus + 500
public:
    Shadowmourne(Hero* _owner);
    ~Shadowmourne();
    void add_effect() override;
    void rm_effect() override;
};

class DeathbringersWill : public Accessory { // id = 3, damage all units in squad on 50
public:
    DeathbringersWill(Hero* _owner);
    ~DeathbringersWill() {};

    void visit(Warrior* unit) override;
};

class Flask : public Accessory { // id = 4, heal all units in squad per 100
public:
    Flask(Hero* _owner);
    ~Flask() {};

    void visit(Warrior* unit) override;
};
