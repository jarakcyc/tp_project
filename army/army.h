#pragma once
#include <string>

using namespace std;

class Warrior {
public:
	Warrior() = default;
	Warrior(string _name, int _health, int _attack, int _cost);
	void info();
	string name;
	int health;
	int attack;
	int cost;
};

class Infantry : public Warrior {
public:
	Infantry() = default;
	Infantry(string _name, int _health, int _attack, int _cost);
};

class Mag : public Warrior {
public:
	Mag();
	Mag(string _name, int _health, int _attack, int _cost);
};

class Special : public Warrior {
public: 
	Special();
	Special(string _name, int _health, int _attack, int _cost);
};