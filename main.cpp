#include "gameplay.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

void fail() {
    cout << "incorrect" << endl;
}

void makeStep(int player_id, Barracks& barracks) {
}

void initialize() {
    HordeFactory = new HordeArmyFactory();
    AlianceFactory = new AlianceArmyFactory();
    manager = new HeroManager();
}

int main() {
    initialize();

    cout << "Hello, please enter number of players!" << endl;
    int nPlayers;
    cin >> nPlayers;

    barracks.resize(nPlayers);
    armies.resize(nPlayers);
    castle.resize(nPlayers, 10000);
    money.resize(nPlayers, 0);

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