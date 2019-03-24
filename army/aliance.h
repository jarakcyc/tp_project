#pragma once
#include "army.h"

class Soldier : public Infantry {
public:
    Soldier();
};

class Mag : public Distance {
public:
    Mag();
};

class AlianceArmyFactory : public ArmyFactory {
public:
    Infantry* create_infantry(const string _name) override;
    Distance* create_distance(const string _name) override;
};