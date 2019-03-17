#include "army.h"
#include <iostream>
#include <string>

using namespace std;

Warrior::Warrior(string _name, attack_type _type, int _health, int _damage, int _cost) :
	name(_name),
	type(_type),
	health(_health),
	damage(_damage),
	cost(_cost)
{}

void Warrior::info() {
	cout << "name: " << name << endl;
	cout << "health: " << health << endl;
	cout << "attack: " << damage << endl;
}

Infantry::Infantry(string _name, int _health, int _damage) :
	Warrior(_name, attack_type::CLOSE, _health, _damage, 100)
{}

Distance::Distance(string _name, int _health, int _damage) :
	Warrior(_name, attack_type::DISTANCE, _health, _damage, 200)
{}

Special::Special(string _name, attack_type _type, int _health, int _damage) :
	Warrior(_name, _type, _health, _damage, 300)
{}