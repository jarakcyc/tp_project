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

Thrall::Thrall():
    Hero("Thrall", 1000, 400)
{}

Zuljin::Zuljin():
    Hero("Zuljin", 800, 600)
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
    } else {
        //cout << "new infantry: " << endl;
        //unit->info();
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
    } else {
        //cout << "new distance: " << endl;
        //unit->info();
    }
    return unit;
}

Hero* HordeArmyFactory::create_hero(const string _name) {
    Hero* unit = nullptr;
    if (_name == "Thrall") {
        unit = new Thrall();
    } else if (_name == "Zuljin") {
        unit = new Zuljin();
    }

    if (unit == nullptr) {
        cout << "no units with the same name" << endl;
    } else {
        //cout << "new hero: " << endl;
        //unit->info();
    }
    return unit;
}
