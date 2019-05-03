#include "horde.h"
#include "aliance.h"
#include "army.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

ArmyFactory* HordeFactory;
ArmyFactory* AlianceFactory;

HeroBuilder* tank;
HeroBuilder* damager;
HeroBuilder* heal;
HeroManager* manager;

vector<Barracks> barracks;
vector<Army> armies;
vector<ArmyFactory*> factories;

class Command {
public:
    virtual ~Command() {};
    virtual void execute(vector<string> params) {};
};

class CreateCommand : public Command {
public:
};

class MakeSquadCommand : public Command {
public:
};

class AddToSquadCommand : public Command {
public:
};

class AttackCommand : public Command {
public:
};

class DefendCommand : public Command {
public:
};

class Invoker {
private:
    Command* command;
public:
};

void fail() {
    cout << "incorrect" << endl;
}

void initialize() {
    ArmyFactory* HordeFactory = new HordeArmyFactory();
    ArmyFactory* AlianceFactory = new AlianceArmyFactory();

    HeroBuilder* tank = new TankBuilder();
    HeroBuilder* damager = new DamagerBuilder();
    HeroBuilder* heal = new HealBuilder();
    HeroManager* manager = new HeroManager();
}

void makeStep(int player_id, Barracks& barracks) {
}

int main() {
    initialize();

    cout << "Hello, please enter number of players!" << endl;
    int nPlayers;
    cin >> nPlayers;

    barracks.resize(nPlayers);
    armies.resize(nPlayers);

    for (int i = 0; i < nPlayers; ++i) {
        cout << i + 1 << " player's step" << endl;
        cout << "Please chose your faraction A or H(Aliance/Horde)" << endl;
        string s;
        while (cin >> s) {
            if (s.size() > 1)
                fail();
            else if (s[0] == 'H') {
                factories.push_back(HordeFactory);
                break;
            } else if (s[0] == 'A') {
                factories.push_back(AlianceFactory);
                break;
            } else 
                fail();
        }
    }

    while (1) {
        for (int i = 0; i < nPlayers; ++i) {
            cout << i + 1 << " player's step" << endl;
            makeStep(i, barracks[i]);
        }
    }
    return 0;
}