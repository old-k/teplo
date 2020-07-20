//============================================================================
// Name        : test5.cpp
// Author      : Alex
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "Settings.hpp"
using namespace std;

int main() {

	GeneralSettings stt = SettingsManager::get();
	bool v = SettingsManager::is_valid(stt);
	if (v)
		cout << "Valid!" << endl; // prints !!!Hello World!!!
	else
		cout << "NOT valid!" << endl; // prints !!!Hello World!!!

	return 0;
}
