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

Infantry* HordeArmyFactory::create_infantry(const string _name) {
    Infantry* unit = nullptr;
    if (_name == "Orc") {
        unit = new Orc();
    } else if (_name == "Tauren") {
        unit = new Tauren();
    }

    if (unit == nullptr) {
        cout << "no units with the same name" << endl;
    }
    return unit;
}

Distance* HordeArmyFactory::create_distance(const string _name) {
    Distance* unit = nullptr;
    if (_name == "Warlock") {
        unit = new Warlock();
    } else if (_name == "Shaman") {
        unit = new Shaman();
    }

    if (unit == nullptr) {
        cout << "no units with the same name" << endl;
    }
    return unit;
}
