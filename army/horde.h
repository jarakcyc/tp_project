#include "army.h"

class HordeInfantry : public Infantry {
public:
	HordeInfantry() = default;
};

class HordeMag : public Mag {
public:
	HordeInfantry();
};

class HordeSpecial : public Special {
public:
	HordeInfantry();
};