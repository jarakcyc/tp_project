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

AlianceArmyFactory::AlianceArmyFactory() {
    i_list.push_back(Soldier());
    i_list.push_back(Knight());

    d_list.push_back(Mag());
    d_list.push_back(Priest());
}
