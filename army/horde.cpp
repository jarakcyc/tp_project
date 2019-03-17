#include "horde.h"

HordeInfantry::HordeInfantry() :
	Infantry("Orc", 400, 100)
{}

HordeDistance::HordeDistance() :
	Distance("Warlock", 200, 200);
{}

HordeSpecial::HordeSpecial() :
	Special("Dragon", attack_type::DISTANCE, 800, 400);
{}