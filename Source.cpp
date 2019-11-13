#include <string>
#include <vector>
#include <iostream>
#include <exception>
#include "Ad.h"

using namespace std;

int main()
{
	Ad reklam("Namnet", "Texten");

	reklam.SetType(AdType::SCROLL);

	// Printa ut shit

	cout << reklam.GetName();

	if (reklam.GetType() == AdType::SCROLL) {
		cout << "It werks";
	}

	// Provar skapa 10 st
	vector<Ad> listan;

	for (int i = 0; i < 15; i++) {
		listan.push_back(Ad("Namn", "text"));
	}

	for (Ad i : listan) {
		cout << i.GetName() << endl;
	}
}