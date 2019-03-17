#pragma once
#include <string>

using namespace std;

enum attack_type {
	CLOSE
	DISTANCE
}

class Warrior {
public:
	Warrior() = default;
	Warrior(string _name, attack_type _type, int _health, int _damage, int _cost);
	void info();
	string name;
	attack_type type;
	int health;
	int damage;
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