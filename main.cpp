#include "horde.h"
#include "aliance.h"
#include "army.h"
#include <iostream>
#include <string>

using namespace std;

void make_step(const string& command, ArmyFactory* factory, Army* army) {
}

int main() {
    cout << "Hello, please change your fraction!(Aliance/Horde)" << endl;

    Army* army = new Army();
    ArmyFactory* factory = nullptr;

    string race = "";
    while (cin >> race) {
        if (race == "Horde") {
            cout << "You choose Horde!" << endl;
            factory = new HordeArmyFactory();
            break;
        } else if (race == "Aliance") {
            cout << "You choose Aliance!" << endl;
            factory = new AlianceArmyFactory();
            break;
        } else {
            cout << "unknown race" << endl;
        }
    }

    string command = "";
    while (cin >> command) {
        make_step(command, factory, army);
    }
    return 0;
}