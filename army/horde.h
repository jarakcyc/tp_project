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

//Heroes
class Thrall : public Hero {
public: 
	Thrall();
};

class Zuljin : public Hero {
public: 
	Zuljin();
};

class HordeArmyFactory : public ArmyFactory {
public:
    Infantry* create_infantry(const string _name) override;
    Distance* create_distance(const string _name) override;
    Hero* create_hero(const string _name) override;
};
