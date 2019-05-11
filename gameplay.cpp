#include "gameplay.h"
#include <algorithm>

ArmyFactory* HordeFactory;
ArmyFactory* AlianceFactory;

HeroManager* manager;

vector<Army> armies;
vector<ArmyFactory*> factories;

vector<deque<pair<int, Warrior*> > > enemies; // {player_id, unit}
vector<deque<pair<int, Warrior*> > > waitroom;

vector<int> money;
vector<int> castle;

void initialize(int nPlayers) {
    HordeFactory = new HordeArmyFactory();
    AlianceFactory = new AlianceArmyFactory();
    manager = new HeroManager();

    armies.resize(nPlayers);
    castle.resize(nPlayers, 10000);
    money.resize(nPlayers, 0);
    enemies.resize(nPlayers);
    waitroom.resize(nPlayers);
}

void init_factories() {
    // initialize factories
}

void fail() {
    cout << "incorrect" << endl;
}

void battle(Warrior* w1, Warrior* w2) {
    w1->health -= w2->damage;
    w2->health -= w1->damage;
}

int to_int(string s) {
    int res = 0;
    for (char c : s)
        res = res * 10 + (c - '0');
    return res;
}

string to_str(int n) {
    string res = "";
    if (n == 0)
        res = "0";
    while (n) {
        res += char(n % 10 + '0');
        n /= 10;
    }
    reverse(res.begin(), res.end());
    return res;
}

void Invoker::set_command(Command* _command) {
    command = _command;
}

void Invoker::exec_command(vector<string> params) {
    command->execute(params);
}

void CreateCommand::execute(vector<string> params) {
    int player_id = to_int(params[0]);
    string type = params[1];
    string name = params[2];

    if (type == "i") {
        armies[player_id].add_infantry(factories[player_id], name, money[player_id]);
    }
    else if (type == "d") {
        armies[player_id].add_distance(factories[player_id], name, money[player_id]);
    }
    else if (type == "h") {
        armies[player_id].add_hero(manager, name, money[player_id]);
    }
}

void AttackCommand::execute(vector<string> params) {
    int from_id = to_int(params[0]);
    int to_id = to_int(params[1]);
    int unit_id = to_int(params[2]);

    if (unit_id >= (int)armies[from_id].units.size())
        return;

    Warrior*& unit = armies[from_id].units[unit_id];

    if (unit->target != -1) {
        int target = unit->target;
        waitroom[target].erase(find(waitroom[target].begin(), waitroom[target].end(), make_pair(from_id, unit)));
    }

    unit = new BattleDecorator(unit, to_id);
    waitroom[to_id].push_back(make_pair(from_id, unit));
}

void DefendCommand::execute(vector<string> params) {
    int player_id;
    int unit_id;

    if ((int)enemies[player_id].size() == 0) 
        return;

    if (unit_id >= (int)armies[player_id].units.size())
        return;

    Warrior*& unit = armies[player_id].units[unit_id];

    if (unit->target != -1) {
        cout << "can't take this unit, he is in battle" << endl;
        return;
    } else {
        pair<int, Warrior*> enemy = enemies[player_id].front();
        enemies[player_id].pop_front();

        battle(unit, enemy.second);

        waitroom[player_id].push_back(enemy);
    }
}

vector<string> ProxyInvoker::parse(int player_id, string args) {
    vector<string> words;

    string cur = "";
    for (char c : args) {
        if (c == ' ' || c == '\n') {
            if (cur != "") {
                words.push_back(cur);
            }
            cur = "";
        } else {
            cur += c;
        }
    }

    if ((int)words.size() == 0)
        return words;

    vector<string> params;
    if (words[0] == "mk") {
        params.push_back(to_str(player_id));
    } else if (words[0] == "atc") {
    } else if (words[0] == "def") {
    } else if (words[0] == "info") {
    }
}
