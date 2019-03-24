#pragma once
#include "army.h"
#include <string>
#include <iostream>

using namespace std;

class Hero;

enum item_type {
    WEAPON,
    ACCESSORY
};

class Item {
public:
    Item(Hero* _owner, const int _item_id, const string _name, const item_type _type, const string _desc);
    virtual ~Item() {};

    Hero* owner;
    const int item_id;
    const string name;
    const item_type type;
    const string description;
    void info() const;

    virtual void const_effect() {};
    virtual void rm_const_effect() {};

    virtual void time_effect() {};
    virtual void rm_time_effect() {};
};

class Weapon : public Item {
public:
    Weapon(Hero* _owner, const int _id, const string _name, const string _desc);
};

class Accessory : public Item {
public:
    Accessory(Hero* _owner, const int _id, const string _name, const string _desc);
};


class Warmace : public Weapon {
public:
    Warmace(Hero* _owner);
    void const_effect() override;
    void rm_const_effect() override;
};

class DeathbringersWill : public Accessory {
public:
    DeathbringersWill(Hero* _owner);
    void time_effect() override;
    void rm_time_effect() override;
};
