#pragma once
#include "army.h"

//Infantries
class Soldier : public Infantry {
public:
    Soldier();
};

class Knight : public Infantry {
public:
	Knight();
};

//Distance
class Mag : public Distance {
public:
    Mag();
};

class Priest : public Distance {
public:
	Priest();
};

class AlianceArmyFactory : public ArmyFactory {
public:
    Infantry* create_infantry(const string _name) override;
    Distance* create_distance(const string _name) override;
};
