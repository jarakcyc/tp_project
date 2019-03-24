#include "horde.h"
#include <iostream>

using namespace std;

Orc::Orc() :
    Infantry("Orc", 400, 100)
{}

Warlock::Warlock() :
    Distance("Warlock", 200, 200)
{}

Infantry* HordeArmyFactory::create_infantry(const string _name) {
    if (_name == "Orc") {
        Infantry* unit = new Orc();
        return unit;
    }
    cout << "no units with the same name" << endl;
    return nullptr;
}

Distance* HordeArmyFactory::create_distance(const string _name) {
    if (_name == "Warlock") {
        Distance* unit = new Warlock();
        return unit;
    }
    cout << "no units with the same name" << endl;
    return nullptr;
}