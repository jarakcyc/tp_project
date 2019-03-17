#include "army.h"
#include <iostream>
#include <string>

using namespace std;

Warrior::Warrior(string _name, attack_type, _type, int _health, int _damage, int _cost) :
	name(_name),
	type(_type),
	health(_health),
	damage(_damage),
	cost(_cost)
{}

void Warrior::info() {
	cout << "name: " << name << endl;
	cout << "health: " << health << endl;
	cout << "attack: " << attack << endl;
}

int main() {
	cout << "ok" << endl;
}