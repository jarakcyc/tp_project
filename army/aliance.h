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
	AlianceArmyFactory();
};
