#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <exception>
#include "AdType.h"

using namespace std;

class Ad
{

private:

	string name;
	string adText;
	AdType adType; 
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

	AdType GetType()
	{
		return adType;
	}

	void SetType(AdType type)
	{
		this->adType = type
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