#pragma once
#include "army.h"

class Orc : public Infantry {
public:
    Orc();
};

class Warlock : public Distance {
public:
    Warlock();
};

class HordeArmyFactory : public ArmyFactory {
public:
    Infantry* create_infantry(const string _name) override;
    Distance* create_distance(const string _name) override;
};