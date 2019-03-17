#pragma once

class Warrior {
public:
	Warrior() = default;
	~Warrior() = default;
	int health;
	int attack;
	int cost;
}

class Infantry : public Warrior {
public:
	Infantry();
	~Infantry();
}

class AlianceInfantry : public Infantry {
public:
	HordeInfantry();
	~HordeInfantry();
}

class HordeInfantry : public Infantry {
public:
	HordeInfantry();
	~HordeInfantry();
}

class Mag : public Warrior {
public:
	Mag();
	~Mag();
}

class AlianceMag : public Infantry {
public:
	HordeInfantry();
	~HordeInfantry();
}

class HordeMag : public Infantry {
public:
	HordeInfantry();
	~HordeInfantry();
}

class Special : public Warrior {
public: 
	Special();
	~Special();
}

class AlianceSpecial : public Infantry {
public:
	HordeInfantry();
	~HordeInfantry();
}

class HordeSpecial : public Infantry {
public:
	HordeInfantry();
	~HordeInfantry();
}