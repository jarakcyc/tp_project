#include "gameplay.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

void makeStep(int player_id) {
}

int main() {
    cout << "Hello, please enter number of players!" << endl;
    int nPlayers;
    cin >> nPlayers;

    initialize(nPlayers);

    while (1) {
        for (int i = 0; i < nPlayers; ++i) {
            cout << i + 1 << " player's step" << endl;
            makeStep(i);
        }
    }
    return 0;
}