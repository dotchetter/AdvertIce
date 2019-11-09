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
	string adType;
	int id;
	int GenerateUniqueId()
	{
		
		id = rand();
		return id;
		
	}
			
public:
	Ad(string name,string text)
	{
		this->name = name;
		this->adText = text;
		
	}
	string GetName()
	{
		return name;
	}
	void SetName()
	{}
	int GetId()
	{
		
		{
			return id;
		}
		
	}
	void SetId()
	{
		this->id = GenerateUniqueId();
	}
	string GetType()
	{
		return adType;
	}
	void SetType()
	{}
	string GetText()
	{
		return adText;
	}
	void SetText()
	{}
	
};

int main()
{
	srand((unsigned long int)time(0));

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
		
		

	
		

	
	



		









