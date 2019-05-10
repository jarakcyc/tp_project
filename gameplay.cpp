#include "gameplay.h"
#include <algorithm>

inline int to_int(string s) {
    int res = 0;
    for (char c : s)
        res = res * 10 + (c - '0');
    return res;
}

inline string to_str(int n) {
    string res = "";
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
        barracks[player_id].add_infantry(factories[player_id], name, money[player_id]);
    }
    else if (type == "d") {
        barracks[player_id].add_distance(factories[player_id], name, money[player_id]);
    }
    else if (type == "h") {
        barracks[player_id].add_hero(manager, name, money[player_id]);
    }
}

