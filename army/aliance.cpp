#include "aliance.h"
#include <iostream>

using namespace std;

Soldier::Soldier() :
    Infantry("Soldier", 400, 100)
{}

Knight::Knight() :
    Infantry("Knight", 600, 200)
{}

Mag::Mag() :
    Distance("Mag", 300, 300)
{}

Priest::Priest() :
    Distance("Priest", 300, 400)
{}

Infantry* AlianceArmyFactory::create_infantry(const string _name) {
    Infantry* unit = nullptr;
    if (_name == "Soldier") {
        unit = new Soldier();
    } else if (_name == "Knight") {
        unit = new Knight();
    }

    if (unit == nullptr) {
        cout << "no units with the same name" << endl;
    }
    return unit;
}

Distance* AlianceArmyFactory::create_distance(const string _name) {
    Distance* unit = nullptr;
    if (_name == "Mag") {
        unit = new Mag();
    } else if (_name == "Priest") {
        unit = new Priest();
    }

    if (unit == nullptr) {
        cout << "no units with the same name" << endl;
    }
    return unit;
}
