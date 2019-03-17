#include "army.h"
#include <iostream>
#include <string>

using namespace std;

Warrior::Warrior(string _name, int _health, int _attack, int _cost) :
	name(_name),
	health(_health),
	attack(_attack),
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