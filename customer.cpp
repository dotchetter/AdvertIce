#include <iostream>
#include <vector>
#include <cstdlib>

/* 
Advertice source code.
Feature: Customer class

Specified requirements according to design doc:

Name: String
ID: Int
Campaigns: Vector

*/

using namespace std;

class Customer 
{
	string name;
	int id;
	vector<string> campaigns;

public:
	Customer(string name, int id)
	{
		this->name = name;
		this->id = id;
	}

	string GetName() 
	{
		return name;
	}

	string SetName(string name) 
	{
		this->name = name;
	}

	int GetId()
	{
		return id;
	}

	int SetId(int id) 
	{
		this->id = id;
	}

	bool hasActiveCampaigns()
	{
		for (campaign i : campaigns) // Returnera om någon av kampanjerna är i nuvarande tidsscope.
		{
			if (i.IsActive()) {
				return true;
			}
		}
	} return false;
};

int main() 
{
	Customer t("test", 123);
	cout << t.GetName();
}