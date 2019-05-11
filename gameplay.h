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

int to_int(const string s);
string to_str(const int n);
bool is_pos_int(string s);

void initialize(int nPlayers);

void init_factories(int nPlayers);

void battle(Warrior* w1, Warrior* w2);

void funeral(int player_id, int unit_id);

class Command {
public:
    virtual ~Command() {};
    virtual void execute(vector<string> params) {};
};

class CreateCommand : public Command {
public:
    void execute(vector<string> params) override;
};

class AttackCommand : public Command {
public:
    void execute(vector<string> params) override;
};

class DefendCommand : public Command {
public:
    void execute(vector<string> params) override;
};

class RelaxCommand : public Command {
public:
    void execute(vector<string> params) override;
};

class InfoCommand : public Command {
public:
    void execute(vector<string> params) override;
};

class Invoker {
private:
    Command* command;
public:
    virtual ~Invoker() {};

    virtual void set_command(Command* _command);
    virtual void exec_command(vector<string> params);
};

class ProxyInvoker : public Invoker {
private:
    Invoker* invoker;
public:
    ProxyInvoker() {invoker = new Invoker();}
    ~ProxyInvoker() {delete invoker;}

    vector<string> get_words(string s);
    bool parse(int player_id, string args);

    void set_command(Command* _command) override {};
    void exec_command(vector<string> params) override {};
};