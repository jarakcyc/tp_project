#pragma once
#include <string>

using namespace std;

enum attack_type {
	CLOSE,
	DISTANCE
};

class Warrior {
public:
	Warrior();
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
	Infantry(string _name, int _health, int _damage);
};

class Distance : public Warrior {
public:
	Distance(string _name, int _health, int _damage);
};

class Special : public Warrior {
public: 
	Special(string _name, attack_type _type, int _health, int _damage);
};