#include <string>
#include <vector>
#include <iostream>
#include <exception>
#include <time.h>
#include <stdlib.h>
#include <algorithm>

using namespace std;

class Ad 
{

private:

	string name;
	string adText; 
	string adType; // Mockup
	int id;

public:

	Ad(string name, string text)
	{
		this->name = name;
		this->adText = text;	
	}

	string GetName()
	{
		return name;
	}

	void SetName(string name)
	{
		this->name = name; // Inkludera felhantering och datavalidering
	}

	int GetId()
	{
		return id;
	}

	void SetId(int id)
	{
		this->id = id;
	}

	string GetType()
	{
		return adType;
	}

	void SetType(AdType type)
	{
		this->adtype = type
	}

	string GetText()
	{
		return adText;
	}

	void SetText(string adText)
	{
		this->adText = adText;
	}
	
};

int main()
{

	Ad ad("Anton Norell\n", "Norell och Nilsson bilskador Abn");
	cout << ad.GetName() << ad.GetText() << endl;
	ad.SetId();
	cout << ad.GetId() <<endl;

	Ad ad2("pfdgkfz\n", "fgolzfkm Ab");
	cout << ad.GetName() << ad.GetText() << endl;
	ad.SetId();
	cout << ad.GetId();

	getchar();
}
		
		

	
		

	
	



		









