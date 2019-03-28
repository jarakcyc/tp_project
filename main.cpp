#include "horde.h"
#include "aliance.h"
#include "army.h"
#include <iostream>
#include <string>

using namespace std;

HeroBuilder builder;

void make_step(const string& command, ArmyFactory* factory, Army* army) {
    if (command == "create") {
        string type, name;
        cin >> type;
        if (type == "infantry") {
            string name;
            cin >> name;
            army->add_infantry(factory, name);
        } else if (type == "distance") {
            string name;
            cin >> name;
            army->add_distance(factory, name);
        } else if (type == "hero") {
            string name;
            cin >> name;
            army->add_hero(factory, name);
        } else {
            cout << "unknown type" << endl;
        }
        return;
    } else if (command == "add_item") {
        string name;
        cin >> name;
        for (int i = 0; i < (int)army->hero.size(); ++i) {
            if (army->hero[i]->name == name) {
                builder.set_hero(army->hero[i]);
                int id;
                cin >> id;
                builder.add_item(id);
                return;
            }
        }
        cout << "no such hero" << endl;
        return;
    } else if (command == "remove_item") {
        string name;
        cin >> name;
        for (int i = 0; i < (int)army->hero.size(); ++i) {
            if (army->hero[i]->name == name) {
                builder.set_hero(army->hero[i]);
                int id;
                cin >> id;
                builder.remove_item(id);
                return;
            }
        }
        cout << "no such hero" << endl;
        return;
    } else if (command == "army_info") {
        cout << "count of infantries: " << (int)army->infantry.size() << endl;
        cout << "count of distance: " << (int)army->distance.size() << endl;
        cout << "count of heroes: " << (int)army->hero.size() << endl;
        return;
    } else if (command == "hero_info") {
        string name;
        cin >> name;
        for (int i = 0; i < (int)army->hero.size(); ++i) {
            if (army->hero[i]->name == name) {
                army->hero[i]->info();
                cout << "count of items: " << (int)army->hero[i]->items.size() << endl;
                return;
            }
        }
        cout << "no such hero" << endl;
        return;
    }
    cout << "unknown command" << endl;
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