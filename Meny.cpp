#include <string>
#include <iostream>
#include <cstdlib>

using namespace std;

int main()
{
	cout << "Vad heter ditt företag?";
	string company;
	cin >> company;
	cout << "Okej. Ditt företag heter" << company;
	return 0;
}