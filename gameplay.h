#pragma once
#include "horde.h"
#include "aliance.h"
#include "army.h"
#include <iostream>
#include <string>
#include <vector>

inline int to_int(const string s);
inline string to_str(const int n);

ArmyFactory* HordeFactory;
ArmyFactory* AlianceFactory;

HeroManager* manager;

vector<Barracks> barracks;
vector<Army> armies;
vector<ArmyFactory*> factories;

vector<int> money;
vector<int> castle;

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

    vector<string> parse(string args) {};

    void set_command(Command* _command) override {};
    void exec_command(vector<string> params) override {};
};