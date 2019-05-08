#include "horde.h"
#include <iostream>

using namespace std;

Orc::Orc() :
    Infantry("Orc", 500, 200)
{}

Tauren::Tauren() :
    Infantry("Tauren", 600, 100)
{}

Warlock::Warlock() :
    Distance("Warlock", 400, 200)
{}

Shaman::Shaman() :
    Distance("Shaman", 300, 300)
{}

HordeArmyFactory::HordeArmyFactory() {
    i_list.push_back(Orc());
    i_list.push_back(Tauren());

    d_list.push_back(Warlock());
    d_list.push_back(Shaman());
}
