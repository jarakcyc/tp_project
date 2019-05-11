#include "gameplay.h"
#include <algorithm>

void fail() {
    cout << "incorrect" << endl;
}

ArmyFactory* HordeFactory;
ArmyFactory* AlianceFactory;

HeroManager* manager;

vector<Army> armies;
vector<ArmyFactory*> factories;

vector<deque<pair<int, Warrior*> > > enemies; // {player_id, unit}
vector<deque<pair<int, Warrior*> > > waitroom;

vector<int> money;
vector<int> castle;

ProxyInvoker pi;

void game() {
    cout << "Please enter number of players" << endl;
    int nPlayers;

    bool ok = false;
    while (!ok) {
        try {
            cin >> nPlayers;
            ok = true;
        } catch (...) {
            fail();
        }
    }

    initialize(nPlayers);

    int cnt = nPlayers;
    while (cnt > 1) {
        for (int i = 0; i < nPlayers; ++i) {
            money[i] += 100;

            for (int j = 0; j < (int)armies[i].units.size(); ++i) {
                armies[i].units[j]->update();
            }
        }

        for (int player_id = 0; player_id < nPlayers; ++player_id) {
            // set enemies
            while (!waitroom[player_id].empty()) {
                enemies[player_id].push_back(waitroom[player_id].front());
                waitroom[player_id].pop_front();
            }

            // heroes use artifacts
            for (int i = 0; i < (int)armies[player_id].units.size(); ++i) {
                Warrior*& unit = armies[player_id].units[i];
                if (unit->name == "Hero" && unit->accessory->item_id == 4) {
                    for (int j = 0; j < (int)armies[player_id].units.size(); ++j) {
                        armies[player_id].units[j]->accept(unit->accessory);
                    }
                } else if (unit->name == "Hero" && unit->accessory->item_id == 3) {
                    for (int j = 0; j < (int)enemies[player_id].size(); ++j) {
                        enemies[player_id][j].second->accept(unit->accessory);
                    }
                }
            }

            for (int i = 0; i < (int)enemies[player_id].size(); ++i) {
                Warrior*& unit = enemies[player_id][i].second;
                if (unit->name == "Hero" && unit->accessory->item_id == 4) {
                    for (int j = 0; j < (int)enemies[player_id].size(); ++j) {
                        if (enemies[player_id][i].first == enemies[player_id][j].first) {
                            enemies[player_id][j].second->accept(unit->accessory);
                        }
                    }
                } else if (unit->name == "Hero" && unit->accessory->item_id == 3) {
                    for (int j = 0; j < (int)armies[player_id].units.size(); ++j) {
                        armies[player_id].units[j]->accept(unit->accessory);
                    }
                }
            }

            vector<int> dead;
            for (int i = 0; i < (int)armies[player_id].units.size(); ++i) {
                if (armies[player_id].units[i]->health <= 0) {
                    dead.push_back(i);
                }
            }

            while (!dead.empty()) {
                funeral(player_id, dead.back());
            }

            cout << "step of " << player_id << " player" << endl;
            string line;
            while (getline(cin, line)) {
                if (!pi.parse(player_id, line)) {
                    break;
                }
            }
        }

        cnt = 0;
        for (int i = 0; i < nPlayers; ++i) {
            if (castle[i] > 0) {
                cnt++;
            }
        }
    }

    cout << "Game over" << endl;
}

void funeral(int player_id, int unit_id) {
    Warrior*& unit = armies[player_id].units[unit_id];

    if (unit->target != -1) {
        int target = unit->target;
        waitroom[target].erase(find(waitroom[target].begin(), waitroom[target].end(), make_pair(player_id, unit)));
    }

    armies[player_id].units.erase(armies[player_id].units.begin() + unit_id);
    delete unit;
}

void initialize(int nPlayers) {
    HordeFactory = new HordeArmyFactory();
    AlianceFactory = new AlianceArmyFactory();
    manager = new HeroManager();

    armies.resize(nPlayers);
    castle.resize(nPlayers, 10000);
    money.resize(nPlayers, 0);
    enemies.resize(nPlayers);
    waitroom.resize(nPlayers);

    init_factories(nPlayers);
}

void init_factories(int nPlayers) {
    for (int i = 0; i < nPlayers; ++i) {
        cout << i << " player's step" << endl;
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
}

void battle(Warrior* w1, Warrior* w2) {
    if (w2->health > 0) {
        w1->health -= w2->damage;
    }
    if (w1->health > 0) {
        w2->health -= w1->damage;
    }
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

bool is_pos_int(string s) {
    for (char c : s) {
        if (c < '0' || c > '9')
            return false;
    }
    return true;
}

void Invoker::set_command(Command* _command) {
    command = _command;
}

void Invoker::exec_command(vector<string> params) {
    command->execute(params);
    delete command;
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
    else {
        fail();
    }
}

void AttackCommand::execute(vector<string> params) {
    int from_id = to_int(params[0]);
    int to_id = to_int(params[1]);
    int unit_id = to_int(params[2]);

    for (int i = 1; i < 3; ++i) {
        if (!is_pos_int(params[i])) {
            fail();
            return;
        }
    }

    if (to_id >= (int)armies.size()) {
        fail();
        return;
    }

    if (unit_id >= (int)armies[from_id].units.size()) {
        fail();
        return;
    }

    try {
        Warrior*& unit = armies[from_id].units[unit_id];

        if (unit->target != -1) {
            int target = unit->target;
            waitroom[target].erase(find(waitroom[target].begin(), waitroom[target].end(), make_pair(from_id, unit)));
        }

        unit = new BattleDecorator(unit, to_id);
        waitroom[to_id].push_back(make_pair(from_id, unit));
    }
    catch (...) {
        fail();
    }
}

void DefendCommand::execute(vector<string> params) {
    int player_id = to_int(params[0]);
    int unit_id = to_int(params[1]);

    if (!is_pos_int(params[1]) && params[1] != "-") {
        fail();
        return;
    }

    if (player_id >= (int)enemies.size()) {
        fail();
        return;
    }

    if ((int)enemies[player_id].size() == 0) {
        cout << "no enemies" << endl;
        return;
    }

    if (unit_id >= (int)armies[player_id].units.size()) {
        fail();
        return;
    }

    if (params[1] == "-") {
        try {
            pair<int, Warrior*> enemy = enemies[player_id].front();
            enemies[player_id].pop_front();

            castle[player_id] -= enemy.second->damage;

            waitroom[player_id].push_back(enemy);
        }
        catch (...) {
            fail();
        }
        return;
    }

    try {
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
    catch (...) {
        fail();
    }
}

void RelaxCommand::execute(vector<string> params) {
    int player_id = to_int(params[0]);

    if (!is_pos_int(params[1])) {
        fail();
        return;
    }

    int unit_id = to_int(params[1]);

    if (unit_id >= (int)armies[player_id].units.size()) {
        fail();
        return;
    }

    try {
        Warrior*& unit = armies[player_id].units[unit_id];

        if (unit->target != -1) {
            int target = unit->target;
            waitroom[target].erase(find(waitroom[target].begin(), waitroom[target].end(), make_pair(player_id, unit)));
        }

        unit = new RelaxDecorator(unit);
    }
    catch (...) {
        fail();
    }
}

void InfoCommand::execute(vector<string> params) {
    int player_id = to_int(params[0]);
    string option = params[1];

    if (is_pos_int(option)) {
        int id = to_int(option);

        if (id >= (int)armies[player_id].units.size()) {
            fail();
        }
        else {
            armies[player_id].units[id]->info();
        }
    } else if (option == "all") {
        for (int i = 0; i < (int)armies[player_id].units.size(); ++i) {
            armies[player_id].units[i]->info();
        }
    } else if (option == "en") {
        for (int i = 0; i < (int)enemies[player_id].size(); ++i) {
            enemies[player_id][i].second->info();
        }
    } else {
        fail();
    }
}

vector<string> ProxyInvoker::get_words(string args) {
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
    if (cur != "")
        words.push_back(cur);

    return words;
}


bool ProxyInvoker::parse(int player_id, string args) {
    vector<string> words = get_words(args);

    if ((int)words.size() == 0) {
        return 1;
    }

    vector<string> params;
    params.push_back(to_str(player_id));
    for (int i = 1; i < (int)words.size(); ++i) {
        params.push_back(words[i]);
    }

    if (words[0] == "mk") { // mk [i/d/h] name
        if ((int)params.size() == 3) {
            invoker->set_command(new CreateCommand());
            invoker->exec_command(params);
        } else {
            fail();
        }
    } else if (words[0] == "atc") { // atk u_id p_id
        if ((int)params.size() == 3) {
            invoker->set_command(new AttackCommand());
            invoker->exec_command(params);
        } else {
            fail();
        }
    } else if (words[0] == "def") { // def u_id
        if ((int)params.size() == 3) {
            invoker->set_command(new DefendCommand());
            invoker->exec_command(params);
        } else {
            fail();
        }
    } else if (words[0] == "rlx") { // rlx u_id
        if ((int)params.size() == 2) {
            invoker->set_command(new RelaxCommand());
            invoker->exec_command(params);
        } else {
            fail();
        }
    } else if (words[0] == "info") { // info [id/all/en]
        if ((int)params.size() == 2) {
            invoker->set_command(new InfoCommand());
            invoker->exec_command(params);
        } else {
            fail();
        }
    } else if (words[0] == "money" && (int)words.size() == 1) {
        cout << money[player_id] << endl;
    } else if (words[0] == "pass" && (int)words.size() == 1) {
        if ((int)enemies[player_id].size() > 0) {
            cout << "enemies are here!" << endl;
        } else {
            return 0;
        }
    }
    return 1;
}
