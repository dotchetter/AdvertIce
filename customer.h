#pragma once
#include <vector>
#include <cstdio>
#include <string>

using namespace std;

class Customer
{
	string name;
	int id;
	vector<Campaign> campaigns;

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

	int GetId()
	{
		return id;
	}
};