#pragma once
#include "army.h"

//Infantries
class Orc : public Infantry {
public:
    Orc();
};

class Tauren : public Infantry {
public:
	Tauren();
};

//Distances
class Warlock : public Distance {
public:
    Warlock();
};

class Shaman : public Distance {
public:
	Shaman();
};

class HordeArmyFactory : public ArmyFactory {
public:
	HordeArmyFactory();
};
