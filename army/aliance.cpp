#include "aliance.h"
#include <iostream>

using namespace std;

Soldier::Soldier() :
    Infantry("Soldier", 200, 100)
{}

Mag::Mag() :
    Distance("Mag", 300, 300)
{}

Infantry* AlianceArmyFactory::create_infantry(const string _name) {
    if (_name == "Soldier") {
        Infantry* unit = new Soldier();
        return unit;
    }
    cout << "no units with the same name" << endl;
    return nullptr;
}

Distance* AlianceArmyFactory::create_distance(const string _name) {
    if (_name == "Mag") {
        Distance* unit = new Mag();
        return unit;
    }
    cout << "no units with the same name" << endl;
    return nullptr;
}