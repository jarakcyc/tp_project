#pragma once
#include "horde.h"
#include "aliance.h"
#include "army.h"
#include <iostream>
#include <string>
#include <vector>
#include <queue>

using namespace std;

void fail();

void game();

int to_int(string s);
string to_str(int n);
bool is_pos_int(string s);

void initialize(const int& nPlayers);

void init_factories(const int& nPlayers);

void battle(Warrior* w1, Warrior* w2);

void funeral(const int& player_id, const int& unit_id);

class Command {
public:
    virtual ~Command() {};
    virtual void execute(const vector<string>& params) {};
};

class CreateCommand : public Command {
public:
    void execute(const vector<string>& params) override;
};

class AttackCommand : public Command {
public:
    void execute(const vector<string>& params) override;
};

class DefendCommand : public Command {
public:
    void execute(const vector<string>& params) override;
};

class RelaxCommand : public Command {
public:
    void execute(const vector<string>& params) override;
};

class InfoCommand : public Command {
public:
    void execute(const vector<string>& params) override;
};

class Invoker {
private:
    Command* command;
public:
    virtual ~Invoker() {};

    virtual void set_command(Command* _command);
    virtual void exec_command(const vector<string>& params);
};

class ProxyInvoker : public Invoker {
private:
    Invoker* invoker;
public:
    ProxyInvoker() {invoker = new Invoker();}
    ~ProxyInvoker() {delete invoker;}

    vector<string> get_words(const string& s);
    bool parse(const int& player_id, const string& args);
};