#include "army.h"

class AlianceInfantry : public Infantry {
public:
	HordeInfantry() = default;
};

class AlianceMag : public Mag {
public:
	HordeInfantry();
};

class AlianceSpecial : public Special {
public:
	HordeInfantry();
};