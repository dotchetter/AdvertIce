#include <string>
#include <vector>
#include <iostream>
#include <exception>
#include "Ad.h"
#include <cstdlib>
#include <ctime>
#include <Windows.h>

using namespace std;

int main()
{
//	Ad reklam("Namnet", "Texten");
//
//	reklam.SetType(AdType::SCROLL);
//
//	// Printa ut shit
//
//	cout << reklam.GetName();
//
//	if (reklam.GetType() == AdType::SCROLL) {
//		cout << "It werks";
//	}
//
//	// Provar skapa 10 st
//	vector<Ad> listan;
//
//	for (int i = 0; i < 15; i++) {
//		listan.push_back(Ad("Namn", "text"));
//	}
//
//	for (Ad i : listan) {
//		cout << i.GetName() << endl;
//	}

//while (true)
//	{ 
//	cout << "What is the name of your company? ";
//	string company;
//	getline(cin, company);
//	cout << "Okay. The Name of your company is" << company;
//	getchar();
//	}


//struct tm startDatum;
//startDatum.tm_year = 119;
//startDatum.tm_mon = 12;
//startDatum.tm_mday = 1;
//startDatum.tm_hour = 0;
//startDatum.tm_min = 0;
//startDatum.tm_sec = 0;
//
//cout << "Din kampanj börjar" << startDatum.tm_year + 1900;
	
	
	vector<string> companies = {"Nothing here!", "Kalle Anka", "Musse pigg", "Nalle Puh" };
	vector<float> payments = {0, 20, 100, 200};
	float total = 0;
	for (float payment : payments)
		total += payment;
	
	vector<float> probabilities;
	for (float payment : payments)
		probabilities.push_back(payment / total);

	vector<float> points;
	points[0] = 0;
	for (int i=1; i < probabilities.size(); i++)
		points[i] += points[i-1];
	
	cout << "Company " << companies[0] << " has " << probabilities[0] << " probability" << endl;
	cout << "Company " << companies[1] << " has " << probabilities[1] << " probability" << endl;
	cout << "Company " << companies[2] << " has " << probabilities[2] << " probability" << endl;
	cout << "Company " << companies[3] << " has " << probabilities[3] << " probability" << endl;

	srand(time(NULL));
	float randomNumber = (float) rand() / RAND_MAX;
	cout << "Random number is " << randomNumber << endl;
	//for (int i=0; i < probabilities.size(); i++)
	if (randomNumber < points[0])
	{
		cout << companies[0] << endl;
	}
	if (points[0] < randomNumber and randomNumber < points[1])
	{
		cout << companies[1] << endl;
	}
	if (points[1] < randomNumber and randomNumber < points[2])
	{
		cout << companies[2] << endl;
	}

return 0;
}